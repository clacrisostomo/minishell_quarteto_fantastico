/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-figu <mde-figu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:23:41 by cfico-vi          #+#    #+#             */
/*   Updated: 2021/11/05 00:02:35 by mde-figu         ###   ########.fr       */
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
	else
		ft_printf("%s: command not found\n", cmd[0]);
	ft_free_split(n_env);
}

/*static void init_pos(char *command, t_pos *posit)
{
	posit->pos_echo = ft_strnstr_indie(command, "echo", ft_strlen(command));
	posit->pos_cd = ft_strnstr_indie(command, "cd", ft_strlen(command));
	posit->pos_pwd = ft_strnstr_indie(command, "pwd", ft_strlen(command));
	posit->pos_exp = ft_strnstr_indie(command, "export", ft_strlen(command));
	posit->pos_uset = ft_strnstr_indie(command, "unset", ft_strlen(command));
	posit->pos_env = ft_strnstr_indie(command, "env", ft_strlen(command));
}*/

// static void parser(char *command, t_pos *posit)
// {
// 	init_pos(command, posit);
// 	if (posit->pos_echo < posit->pos_cd)
// 		echo(command);
// 	else if (ft_strncmp(command, "cd ", 2) == 0)
// 		cd(command);
// 	//else if (!strcmp("exit", command))
// 	//exit();
// }

char	*do_prompt(void)
{
	char	cwd[2048];
	char	*prompt;

	getcwd(cwd, 2048);
	prompt = ft_strjoin(cwd, "$ ");
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
	//t_pos posit;

	i = 0;
	while (1)
	{
		define_signals();
		prompt = do_prompt();
		command = readline(prompt);
		if (!command)
		{
			ft_printf("exit\n");
			errno = 0;
			free_n_exit(g_shell.env);
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
			//printf("%s, %s, %s", cmd[0], cmd[1], cmd[2]);
			free(command);
			//parser(command, &posit);
			execute(cmd);
			ft_free_split(cmd);
		}
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	if (argc > 1 && argv)
	{
		ft_putstr_fd("ERROR: TOO MANY ARGS\n", 2);
		return (EXIT_FAILURE);
	}
	errno = 0;
	g_shell.env = envp_to_hash(envp);
	g_shell.local = create_hash_table(50);
	loop();
	return (1);
}
