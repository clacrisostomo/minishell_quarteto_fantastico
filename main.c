/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-figu <mde-figu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:23:41 by cfico-vi          #+#    #+#             */
/*   Updated: 2021/11/06 00:34:07 by mde-figu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

//TODO: MUDAR AS HASHTABLES
void	execute(char **cmd)
{
	char	**n_env;

	n_env = hash_to_str_arr(g_shell.env);
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
		exit_terminal(cmd, n_env);
	else if (ft_isvar(cmd))
		expt(cmd, 0);
	else if (is_path(cmd, n_env))
		execve(cmd[0], cmd, n_env);
	else if (execve(cmd[0], cmd, n_env) == -1)
		ft_printf("%s: command not found\n", cmd[0]);
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
	int i;

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

static void	loop()
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
			execute(cmd);
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
