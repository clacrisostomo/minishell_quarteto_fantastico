/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-figu <mde-figu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 20:52:52 by mde-figu          #+#    #+#             */
/*   Updated: 2021/10/19 23:27:07 by mde-figu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	execute(char **cmd, char *envp[])
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
	else if (ft_isvar(cmd))
		expt(cmd, 0);
	else if (is_path(cmd, envp))
		execve(cmd[0], cmd, envp);
	else if (execve(cmd[0], cmd, envp) == -1)
	{
		ft_printf("%s: command not found\n", cmd[0]);
	}
	else
		ft_printf("%s: command not found\n", cmd[0]);
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

static void	loop(char *envp[])
{
	char	**cmd;
	char	*command;
	char	*prompt;
	//t_pos posit;
	while (1)
	{
		g_shell.status_error = 0;
		prompt = do_prompt();
		command = readline(prompt);
		free(prompt);
		if (!strcmp("exit", command))
		{
			free(command);
			break ;
		}
		add_history(command);
		cmd = split_command(command);
		free(command);
		//parser(command, &posit);
		execute(cmd, envp);
		ft_free_split(cmd);
	}
	free_all(g_shell.env);
}

int	main(int argc, char *argv[], char *envp[])
{
	if (argc > 1 && argv)
	{
		ft_printf("ERROR: TOO MANY ARGS\n");
		return (0);
	}
	g_shell.env = envp_to_hash(envp);
	g_shell.hash = create_hash_table(50);
	g_shell.temp = create_hash_table(50);
	loop(envp);
	return (1);
}
