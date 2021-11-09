/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-figu <mde-figu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:23:41 by cfico-vi          #+#    #+#             */
/*   Updated: 2021/11/09 01:22:25 by mde-figu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	**get_paths()
{
	char *paths;
	char **ret;
	int	i;

	i = 0;
	paths = search_hash_by_key("PATH");
	while (*paths++ != '\0')
	{
		if (*paths == ':')
			i++;
	}
	ret = (char **)malloc((i + 1) * sizeof(char *));
	ret = ft_split(paths, ':');
	return (ret);
}

void	execute(char **cmd, int i)
{
	char	**n_env;
	int status;
	//char	**paths;
	pid_t	pid;
	int		fd[2];
	//int		c;

	//c = 1;
	//paths = get_paths();
	n_env = hash_to_str_arr(g_shell.env);
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
		exit_terminal(cmd, n_env);
	else if (ft_isvar(cmd))
		expt(cmd, i);
	else if (is_path(cmd, n_env))
	{
		pipe(fd);
		pid = fork();
		if (pid == -1)
		{
			perror("Error: ");
			free_n_exit();
		}
		else if(pid == 0)
			execve(cmd[i], cmd, n_env);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			errno = WIFEXITED(status);
	}
/* 	else if (execve(paths[0], cmd, n_env) == -1)
	{
		while (paths[c][0] != '\0')
		{
			execve("/bin/", cmd, n_env);
			c++;
		}
	} */
	else if (execve(cmd[i], cmd, n_env) == -1)
		ft_printf("%s: command not found\n", cmd[i]);
/* 	else
		ft_printf("%s: command not found\n", cmd[0]); */
	ft_free_split(n_env);
}

char	*do_prompt(void)
{
	char	cwd[2048];
	char	*prompt;

	getcwd(cwd, 2048);
	prompt = ft_strjoin(cwd, "$ ");
	if (prompt == NULL)
	{
		perror("Error: ");
		free_n_exit();
	}
	return (prompt);
}

void	free_n_env(char **n_env)
{
	int	i;

	i = 0;
	if (n_env)
	{
		while (n_env[i])
		{
			free (n_env[i]);
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

void	save_origin_fd(int *save_fd)
{
	save_fd[0] = dup(0);
	save_fd[1] = dup(1);
}

void	reset_fd(int *save_fd)
{
	dup2(save_fd[0], 0);
	close(save_fd[0]);
	dup2(save_fd[1], 1);
	close(save_fd[1]);
}

void	ms_pipe(char **cmd, int i)
{
	pid_t	pid;
	int	fd[2];
	//int	save_fd[2];

	pid = 0;

	//save_origin_fd(save_fd);
	pipe(fd);
	pid = fork();   
	if (pid == -1)
	{
		perror("Error: ");
		free_n_exit();
	}
	else if (pid != 0)
	{
		waitpid(pid, NULL, 0);
	}
	else if(pid == 0)
	{
	//config_pip
		dup2(fd[1], STDOUT);
		printf("fez fork");
		parser(cmd, i + 1);
		//execute(cmd, c);
	}
}


void	parser(char **cmd, int i)
{
	int c;

	c = i;
	while (!(ft_strcmp(cmd[i], "|")) && !(ft_strcmp(cmd[i], "\0")))
		i++;
	if (!(ft_strcmp(cmd[i], "\0")))
		ms_pipe(cmd, i);
	else
		execute(cmd, c);
}

static void	loop(void)
{
	char	**cmd;
	char	*command;
	char	*prompt;
	int		i;
	int		old_errno;

	i = 0;
	while (1)
	{
		old_errno = errno;
		define_signals();
		prompt = do_prompt();
		command = readline(prompt);
		errno = old_errno;
		if (!command)
		{
			ft_printf("exit\n");
			errno = 0;
			free_n_exit();
		}
		free(prompt);
		while (ft_isalpha(command[i]) == 0 && command[i] != '\0')
			i++;
		if (command[i] == '\0')
		{
			errno = 0;
			free(command);
		}
		else
		{
			add_history(command);
			cmd = split_command(command);
			free(command);
			parser(cmd, 0);
			//execute(cmd);
			ft_free_split(cmd);
		}
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	if (argc > 1 && argv)
	{
		ft_putstr_fd("Error: Too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	g_shell.env = envp_to_hash(envp);
	g_shell.local = create_hash_table(50);
	loop();
	return (1);
}
