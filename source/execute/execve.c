/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfico-vi <cfico-vi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:11:32 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/27 19:12:15 by cfico-vi         ###   ########.fr       */
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

char	**create_command_for_exec(char **cmd, char **paths)
{
	char	*new_path;
	char	**new_cmd;
	int		c;

	c = 0;
	new_cmd = (char **)malloc(2 * sizeof(char *));
	new_cmd[1] = NULL;
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

static void	execve_error(char **cmd)
{
	ft_putstr_fd("Minishell: '", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd("': ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	errno = 127;
}

static void	execute_execve(char **new_cmd, char **cmd, char **n_env)
{
	int			status;
	pid_t		pid;

	status = 0;
	define_child_signals();
	pid = fork();
	if (pid == -1)
	{
		perror("Error: ");
		free_n_exit();
	}
	else if (pid == 0)
	{
		if (new_cmd)
			execve(new_cmd[0], cmd, n_env);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		errno = WEXITSTATUS(status);
}

void	do_exec(char **cmd, char **n_env)
{
	char		**paths;
	char		**new_cmd;

	paths = get_paths();
	new_cmd = NULL;
	new_cmd = create_command_for_exec(cmd, paths);
	if (new_cmd)
		execute_execve(new_cmd, cmd, n_env);
	else
		execve_error(cmd);
	ft_free_split(paths);
	if (new_cmd)
		ft_free_split(new_cmd);
}
