/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:11:32 by nbarreir          #+#    #+#             */
/*   Updated: 2021/11/26 14:11:59 by nbarreir         ###   ########.fr       */
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

void execute(char **cmd, int i, char **old_cmd)
{
	char **n_env;
	int status;
	char **paths;
	pid_t pid;
	//int	ret;
	//int		fd[2];
	int c;
	char **new_cmd;
	char *new_path;
	//char *path;
	//char cwd[2048];

	//ret = 0;
	c = 1;
	paths = get_paths();
	n_env = hash_to_str_arr(g_shell.env);
	new_cmd = NULL;
	if (!(ft_strcmp(cmd[i], "echo")))
		echo(cmd);
	else if (!(ft_strcmp(cmd[i], "cd")))
		cd(cmd);
	else if (!(ft_strcmp(cmd[i], "pwd")))
		pwd();
	else if (!(ft_strcmp(cmd[i], "env")))
		env();
	else if (!(ft_strcmp(cmd[i], "export")))
		expt(cmd, 1);
	else if (!(ft_strcmp(cmd[i], "unset")))
		unset_(cmd);
	else if (!(ft_strcmp(cmd[i], "exit")))
		exit_terminal(cmd, n_env, old_cmd);
	else if (ft_isvar(cmd))
		expt(cmd, i);
	else if (is_path(cmd, n_env))
	{
		pid = fork();
		if (pid == -1)
		{
			perror("Error: ");
			free_n_exit();
		}
		else if (pid == 0)
		{
			execve(*cmd, cmd, n_env);
			errno = 2;
			exit(errno);
		}
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			errno = WIFEXITED(status);
	}
	else //if (execve(paths[0], cmd, n_env) == -1) //<<<<<<<<<<EXECVE SEM PATH
	{
		pid = fork();
		if (pid == -1)
		{
			perror("Error: ");
			free_n_exit();
		}
		else if (pid == 0)
		{
			new_cmd = (char **)malloc(sizeof(char **));
			while (paths[c])
			{
				new_path = ft_strjoin(paths[c], "/");
				new_cmd[0] = ft_strjoin(new_path, cmd[0]);
				if (is_executable(new_cmd[0]))
				{
					//new_cmd[0] = ft_strjoin(new_path, cmd[0]);
					printf("new_cmd= %s", new_cmd[0]);
					execve(new_cmd[0], cmd, n_env);
					break ;
				}
				//printf("path= %s\n",paths[c]);
				//printf("new_path= %s\n", new_path);
				free(new_path);
				//free(new_cmd);
				c++;
			}
			//path = ft_strjoin(getcwd(cwd, 2048), "/");
			//execve(ft_strjoin(path, "minishell"), cmd, n_env);
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
		ft_free_split(new_cmd);
	}
//	else if (execve(cmd[i], cmd, n_env) == -1)
	//	ft_printf("%s: command not found\n", cmd[i]);
	ft_free_split(n_env);
	ft_free_split(paths);
	if (new_cmd)
		ft_free_split(new_cmd);
}

void free_n_env(char **n_env)
{
	int i;

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
	return;
}

void ft_free_split(char **str)
{
	int i;

	i = -1;
	if (!(str))
		return;
	while (*(str + ++i) != NULL)
	{
		free(*(str + i));
		*(str + i) = NULL;
	}
	free(str);
	str = NULL;
}