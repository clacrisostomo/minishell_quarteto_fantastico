/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:46:19 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/10 04:02:24 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_executable(char *new_path)
{
	struct stat	buffer;

	if (stat(new_path, &buffer) != 0)
		return (0);
	if ((buffer.st_mode & S_IXUSR))
		return (1);
	return (0);
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

static void	execve_error(char *cmd)
{
	ft_putstr_fd("Minishell: '", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("': ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	exit(errno);
}

void	do_exec(char **cmd, char **n_env)
{
	int			status;
	char		**paths;
	pid_t		pid;
	char		**new_cmd;

	paths = get_paths();
	new_cmd = NULL;
	define_signals_exec();
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
		execve_error(cmd[0]);
	}
	waitpid(pid, &status, 0);
	errno = WEXITSTATUS(status);
	ft_free_split(paths);
	if (new_cmd)
		ft_free_split(new_cmd);
}
