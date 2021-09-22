/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 20:52:52 by mde-figu          #+#    #+#             */
/*   Updated: 2021/09/22 00:45:39 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_cmd_one(char *cmd)
{
	char	*tmp;
	char	*space;

	if (ft_strncmp(cmd, "cd ", 2) == 0)
	{
		space = ft_strchr(cmd, ' ') + 1;
		tmp = ft_substr(cmd, space - cmd, ft_strlen(space));
		chdir(tmp);
		free (tmp);
	}
	return (1);
}

static void	loop(void)
{
	char	*command;
	char	cwd[2048];
	char	*prompt;

	while (1)
	{
		getcwd(cwd, 2048);
		prompt = ft_strjoin(cwd, "$ ");
		command = readline(prompt);
		free(prompt);
		//printf("%s\n", command);// ev tirar isso
		if (!strcmp("exit", command))
		{
			free (command);
			break ;
		}
		add_history(command);
		exec_cmd_one(command);
		//exec_cmd_two(command);
		free (command);
	}
}

int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	loop();
	return (1);
}
