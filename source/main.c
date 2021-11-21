/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantos- <csantos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:23:41 by cfico-vi          #+#    #+#             */
/*   Updated: 2021/11/110 21:551:0:04 by csantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *get_path_str()
{
	int c;

	c = 0;
	while (g_shell.env->item[c] && c <= g_shell.env->size - 1)
	{
		if (!ft_strcmp(g_shell.env->item[c]->key, "PATH"))
			return (g_shell.env->item[c]->value);
		c++;
	}
	return ("");
}

char **get_paths()
{
	char *paths;
	char **ret;
	/* 	int	i;

	i = 0; */
	paths = get_path_str();
	//printf("retorno do get_path is: %s\n", paths);
	//printf("%i\n", i);
	ret = ft_split(paths, ':');
	//printf("retorno do ret is: %s\n", ret[2]);
	return (ret);
}

void execute(char **cmd, int i)
{
	char **n_env;
	int status;
	char **paths;
	pid_t pid;
	//int		fd[2];
	int c;
	char **new_cmd;
	char *new_path;

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
		exit_terminal(cmd, n_env);
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
	else if (execve(paths[0], cmd, n_env) == -1) //<<<<<<<<<<EXECVE SEM PATH
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
				execve(new_cmd[i], cmd, n_env);
				c++;
			}
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
	else if (execve(cmd[i], cmd, n_env) == -1)
		ft_printf("%s: command not found\n", cmd[i]);
	ft_free_split(n_env);
	ft_free_split(paths);
	if (new_cmd)
		ft_free_split(new_cmd);
}

char *do_prompt(void)
{
	char cwd[2048];
	char *prompt;

	getcwd(cwd, 2048);
	prompt = ft_strjoin(cwd, "$ ");
	if (prompt == NULL)
	{
		perror("Error: ");
		free_n_exit();
	}
	return (prompt);
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

void save_origin_fd(int *save_fd)
{
	save_fd[0] = dup(0);
	save_fd[1] = dup(1);
}

void reset_fd(int *save_fd)
{
	dup2(save_fd[0], 0);
	close(save_fd[0]);
	dup2(save_fd[1], 1);
	close(save_fd[1]);
}

void ms_pipe(char **cmd, int i, int *old_fd)
{
	int fd[2];
	//int	save_fd[2];
	dup2(*old_fd, STDIN);
	if (old_fd != 0)
		close(*old_fd);
	//save_origin_fd(save_fd);
	if (!(ft_strcmp(cmd[i], "|")))
	{
		//ft_putstr_fd("oiiiiii\n", 2);
		pipe(fd);
		dup2(fd[1], STDOUT);
		close(fd[1]);
		*old_fd = dup(fd[0]);
		close(fd[0]);
	}
}

char **cmd_till_pipe(char **cmd, int begin, int end)
{
	char **sub_cmd;
	int k;

	k = 0;
	sub_cmd = (char **)calloc((end - begin + 1), sizeof(char *));
	while (begin != end)
		sub_cmd[k++] = cmd[begin++];
	sub_cmd[k] = NULL;
	return (sub_cmd);
}

void parser(char **cmd, int i, int *old_fd)
{
	int save_fd[2];
	int c;
	char **sub_cmd;

	c = i;
	save_origin_fd(save_fd);

	while (ft_strcmp(cmd[i], "|") && (cmd[i + 1]))
		i++;
	if (!(ft_strcmp(cmd[i], "|")))
		sub_cmd = cmd_till_pipe(cmd, c, i);
	else
		sub_cmd = cmd_till_pipe(cmd, c, i + 1);
	ms_pipe(cmd, i, old_fd);
	//ft_putstr_fd(sub_cmd[0], 2);0 1
	//ft_putstr_fd("\n", 2);
	//ft_putstr_fd(sub_cmd[1], 2);
	//ft_putstr_fd("\n", 2);
	execute(sub_cmd, 0);
	reset_fd(save_fd);
	if (sub_cmd)
		ft_free_split(sub_cmd);
	if (!(ft_strcmp(cmd[i], "|")))
		parser(cmd, i + 1, old_fd);
}

static void loop(void)
{
	char **cmd;
	char *command;
	char *prompt;
	int i;
	int old_errno;
	int old_fd;

	i = 0;
	while (1)
	{
		old_fd = STDIN;
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
			//verifica se tem redirect, troca stdin e stdout
			parser(cmd, 0, &old_fd);
			//execute(cmd);
			//ft_free_split(cmd);
			//volta o stdin e stdout originais
		}
	}
}

int main(int argc, char *argv[], char *envp[])
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
