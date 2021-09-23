/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 20:52:52 by mde-figu          #+#    #+#             */
/*   Updated: 2021/09/22 22:21:06 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	echo(char *cmd)
{
	int	have_n;

	have_n = 0;
	if (ft_strncmp(cmd, "echo -n", 7) == 0)
		have_n = 1;
	printf("%s", cmd);
	if (have_n != 1)
		printf("\n");
	return (1);
}

static int	exec_cmd_one(char *cmd)
{
	char	*tmp;
	char	*space;

	space = ft_strchr(cmd, ' ') + 1;
	tmp = ft_substr(cmd, space - cmd, ft_strlen(space));
	chdir(tmp);
	free (tmp);

	/*if (ft_strncmp(cmd, "cd ", 2) == 0)
	{
		space = ft_strchr(cmd, ' ') + 1;
		tmp = ft_substr(cmd, space - cmd, ft_strlen(space));
		chdir(tmp);
		free (tmp);
	}*/
	return (1);
}
static void	execute(char *command)
{
	if (ft_strncmp(command, "echo ", 4) == 0)
		echo(command);
	else if (ft_strncmp(command, "cd ", 2) == 0)
		exec_cmd_one(command);
	//else if (!strcmp("exit", command))
		//exit();
}

static char	*do_prompt(void)
{
	char	cwd[2048];
	char	*prompt;

	getcwd(cwd, 2048);
	prompt = ft_strjoin(cwd, "$ ");
	return(prompt);
}

static void	loop(void)
{
	char	*command;
	char	*prompt;

	while (1)
	{
		prompt = do_prompt();
		command = readline(prompt);
		free(prompt);
		if (!strcmp("exit", command))
		{
			free (command);
			break ;
		}
		execute(command);
		//exec_cmd_one(command);
		//exec_cmd_two(command);
		add_history(command);
		free (command);
	}
}

int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	if (argc > 1 && argv)
	{
		printf("ERROR: MANY ARGS");
		return (0);
	}
	loop();
	return (1);
}
