/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:11:32 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/05 18:57:57 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtins(char **cmd)
{
	if (!(ft_strcmp(cmd[0], "echo")))
		return (TRUE);
	else if (!(ft_strcmp(cmd[0], "cd")))
		return (TRUE);
	else if (!(ft_strcmp(cmd[0], "pwd")))
		return (TRUE);
	else if (!(ft_strcmp(cmd[0], "env")))
		return (TRUE);
	else if (!(ft_strcmp(cmd[0], "export")))
		return (TRUE);
	else if (!(ft_strcmp(cmd[0], "unset")))
		return (TRUE);
	else if (!(ft_strcmp(cmd[0], "exit")))
		return (TRUE);
	else if (ft_isvar(cmd))
		return (TRUE);
	return (FALSE);
}

static int	is_executable(char *new_path)
{
	struct stat	buffer;

	if (stat(new_path, &buffer) != 0)
		return (0);
	if ((buffer.st_mode & S_IXUSR))
		return (1);
	return (0);
}

void	builtins(char **cmd, char **old_cmd, char **n_env)
{
	if (!(ft_strcmp(cmd[0], "echo")))
		echo(cmd);
	else if (!(ft_strcmp(cmd[0], "cd")))
		cd(cmd);
	else if (!(ft_strcmp(cmd[0], "pwd")))
		pwd();
	else if (!(ft_strcmp(cmd[0], "env")))
		env();
	else if (!(ft_strcmp(cmd[0], "export")))
		expt(cmd, 1);
	else if (!(ft_strcmp(cmd[0], "unset")))
		unset_(cmd);
	else if (!(ft_strcmp(cmd[0], "exit")))
		exit_terminal(cmd, n_env, old_cmd);
	else if (ft_isvar(cmd))
		expt(cmd, 0);
}

char	**create_command_for_exec(char **cmd, char **paths)
{
	char	*new_path;
	char	**new_cmd;
	int		c;

	c = 0;
	new_cmd = (char **)malloc(sizeof(char **));
	if (is_executable(cmd[0]))
		new_cmd[0] = ft_strdup(cmd[0]);
	else
	{
		while (paths[c])
		{
			new_path = ft_strjoin(paths[c], "/");
			new_cmd[0] = ft_strjoin(new_path, cmd[0]);
			free(new_path);
			if (is_executable(new_cmd[0]))
				break ;
			free(new_cmd[0]);
			c++;
		}
	}
	return (new_cmd);
}

void	do_exec(char **cmd, char **n_env)
{
	int			status;
	char		**paths;
	pid_t		pid;
	char		**new_cmd;

	paths = get_paths();
	new_cmd = NULL;
	pid = fork();
	if (pid == -1)
	{
		perror("Error: ");
		free_n_exit();
	}
	else if (pid == 0)
	{
		new_cmd = create_command_for_exec(cmd, paths);
		execve(new_cmd[0], cmd, n_env);
		ft_putstr_fd("Minishell: '", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd("': ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		exit(errno);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		errno = WIFEXITED(status);
	ft_free_split(paths);
	if (new_cmd)
		ft_free_split(new_cmd);
}

void	free_n_env(char **n_env)
{
	int	i;

	i = 0;
	if (n_env)
	{
		while (n_env[i])
		{
			free(n_env[i]);
			i++;
		}
		free(n_env);
	}
	return ;
}

void	ft_free_split(char **str)
{
	int	i;

	i = -1;
	if (!(str))
		return ;
	while (*(str + ++i) != NULL)
	{
		free(*(str + i));
		*(str + i) = NULL;
	}
	free(str);
	str = NULL;
}

void	execute(char **cmd, char **old_cmd)
{
	char	**n_env;

	if (cmd[0] != NULL)
	{
		n_env = hash_to_str_arr(g_shell.env);
		if (is_builtins(cmd))
			builtins(cmd, old_cmd, n_env);
		else
			do_exec(cmd, n_env);
		ft_free_split(n_env);
	}
}
