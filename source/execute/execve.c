/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfico-vi <cfico-vi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:11:32 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/23 14:21:57 by cfico-vi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_executable(char *new_path)
{
	struct stat	buffer;

	if (stat(new_path, &buffer) != 0)
		return (0);
	if ((buffer.st_mode & S_IXUSR))
		return (1);
	return (0);
}

int	has_second_bar(char *cmd)
{
	int	i;
	int	ctn_slash;

	i = 0;
	ctn_slash = 0;
	if (cmd[0] == '.' && cmd[1] == '/')
		return (TRUE);
	while (cmd[i])
	{
		if (cmd[i] == '/')
		{
			ctn_slash++;
			if (ctn_slash >= 2)
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

char	**create_command_for_exec(char **cmd, char **paths)
{
	char	*new_path;
	char	**new_cmd;
	int		c;

	c = 0;
	new_cmd = (char **)malloc(sizeof(char **));
	if (is_executable(cmd[0]) && has_second_bar(cmd[0]))
	{
		new_cmd[0] = ft_strdup(cmd[0]);
		return (new_cmd);
	}
	while (paths[c])
	{
		new_path = ft_strjoin(paths[c], "/");
		new_cmd[0] = ft_strjoin(new_path, cmd[0]);
		free(new_path);
		if (is_executable(new_cmd[0]))
			return (new_cmd);
		free(new_cmd[0]);
		c++;
	}
	free (new_cmd);
	return (NULL);
}

static void	execve_error(char **cmd, char **n_env, char **paths)
{
	ft_putstr_fd("Minishell: '", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd("': ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	ft_free_split(cmd);
	ft_free_split(n_env);
	ft_free_split(paths);
	free_n_exit();
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
		if (new_cmd)
			execve(new_cmd[0], cmd, n_env);
		execve_error(cmd, n_env, paths);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		g_shell.status_error = WEXITSTATUS(status);
		errno = WEXITSTATUS(status);
	}
	printf("errno = %d, status = %d, WTERMSIG = %d\n", errno, status, WEXITSTATUS(status));
	ft_free_split(paths);
	if (new_cmd)
	{
		printf("entrou\n");
		ft_free_split(new_cmd);
	}
}
