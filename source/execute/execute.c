/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantos- <csantos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:11:32 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/01 00:02:41 by csantos-         ###   ########.fr       */
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

/* void	error_free_exit(char *str)
{
	perror(str);
	free_n_exit();
}

void	exec_error_exit(char **cmd, char **n_env, int i)
{
	execve(*cmd, cmd, n_env);
	errno = i;
	exit(errno);
}

void	exec_w_path(char **cmd, char **n_env)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
		error_free_exit("Error: ");
	else if (pid == 0)
		exec_error_exit(cmd, n_env, 2);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		errno = WIFEXITED(status);
}

void	exec_w_o_path(char **cmd, char **n_env, int i)
{
	int status;
	pid_t pid;
	char **path;
	char **new_cmd;
	char **new_paths;
	
	new_cmd = (char **)malloc(sizeof(char **));
	while (1)
	{
		path = ft_strjoin(get_paths(i), "/");
		new_cmd[0] = ft_strjoin(path, cmd[0]);
		if (is_executable(cmd[0]))
		{
			execve(cmd[0], cmd, n_env);
			break;
		}
		else if (is_executable)
		{
			execve(new_cmd[0], cmd, n_env);
			break;
		}
		i++;
	}
}

void	do_exec(char **cmd, char **n_env)
{
	int	i;

	i = 0;
	if (is_path(cmd, n_env))
		exec_w_path(cmd, n_env);
	else
		exec_w_o_path(cmd, n_env, i);
} */

void do_exec(char **cmd, char **n_env)
{
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
	//int	h = 0;
	/* while (cmd[h])
		printf("%s ", cmd[h++]);
	printf("\n"); */
	c = 1;
	paths = get_paths();
	new_cmd = NULL;
	if (is_path(cmd, n_env))
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
				if (is_executable(cmd[0]))
					execve(cmd[0], cmd, n_env);
				else if (is_executable(new_cmd[0]))
				{
					new_cmd[0] = ft_strjoin(new_path, cmd[0]);
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

void	execute(char **cmd, char **old_cmd)
{
	char **n_env;

	if(cmd[0] != NULL)
	{
		n_env = hash_to_str_arr(g_shell.env);
		if (is_builtins(cmd))
			builtins(cmd, old_cmd, n_env);
		else
			do_exec(cmd, n_env);
		ft_free_split(n_env);
	}
}
