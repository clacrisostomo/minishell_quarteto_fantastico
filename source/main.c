/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfico-vi <cfico-vi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:23:41 by cfico-vi          #+#    #+#             */
/*   Updated: 2021/12/24 16:55:08 by cfico-vi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(char **cmd, int i, int *old_fd)
{
	int		save_fd[2];
	int		c;
	char	**sub_cmd;

	c = i;
	if (!have_file_after_redirect(cmd))
	{
		ft_putendl_fd("No file or incorrect file", 2);
		return ;
	}
	save_origin_fd(save_fd);
	while (!is_token_from_quotes("|", cmd[i], i) && cmd[i + 1])
		i++;
	if (!(ft_strcmp(cmd[i], "|")))
		sub_cmd = cmd_till_pipe(cmd, c, i);
	else
		sub_cmd = cmd_till_pipe(cmd, c, i + 1);
	miss_pipe(cmd, i, old_fd);
	sub_cmd = make_command_redirect(sub_cmd, 0, save_fd);
	execute(sub_cmd, cmd);
	reset_fd(save_fd);
	if (sub_cmd)
		ft_free_split(sub_cmd);
	if (!(ft_strcmp(cmd[i], "|")) && (cmd[i + 1]))
		parser(cmd, i + 1, old_fd);
}

static void	command_execute(char *command)
{
	char	**cmd;
	int		old_fd;

	old_fd = 0;
	add_history(command);
	cmd = split_command(command);
	free(command);
	if (cmd[0])
		parser(cmd, 0, &old_fd);
	if (cmd)
	{
		ft_free_split(cmd);
		free_escapes();
	}
}

static void	loop_command(char *command)
{
	int		i;

	i = 0;
	if (!command)
	{
		ft_printf("exit\n");
		errno = 0;
		free_n_exit();
	}
	while (ft_isprint(command[i]) == 0 && command[i] != '\0')
		i++;
	if (command[i] == '\0')
	{
		errno = 0;
		free(command);
	}
	else
		command_execute(command);
}

static void	loop(void)
{
	char	*command;
	char	*prompt;

	while (TRUE)
	{
		g_shell.ms_errno = errno;
		g_shell.esc_idx = NULL;
		define_interactive_signals();
		prompt = do_prompt();
		command = readline(prompt);
		free(prompt);
		errno = g_shell.ms_errno;
		loop_command(command);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	if (argc > 1 && argv)
	{
		ft_putstr_fd("Error: Too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	g_shell.env = envp_to_array(envp);
	g_shell.local = create_array_table(50);
	loop();
	return (1);
}
