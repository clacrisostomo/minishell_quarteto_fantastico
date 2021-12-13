/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:44:16 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/10 18:17:30 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parser(char **cmd, int i, int *old_fd, int has_pipe)
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
	while (ft_strcmp(cmd[i], "|") && (cmd[i + 1]))
		i++;
	if (!(ft_strcmp(cmd[i], "|")))
		sub_cmd = cmd_till_pipe(cmd, c, i);
	else
		sub_cmd = cmd_till_pipe(cmd, c, i + 1);
	has_pipe = miss_pipe(cmd, i, old_fd, has_pipe);
	sub_cmd = make_command_redirect(sub_cmd, 0, save_fd);
	execute(sub_cmd, cmd, has_pipe);
	reset_fd(save_fd);
	if (sub_cmd)
		ft_free_split(sub_cmd);
	if (!(ft_strcmp(cmd[i], "|")) && (cmd[i + 1]))
		parser(cmd, i + 1, old_fd, has_pipe);
}

static void	command_execute(char *command)
{
	char	**cmd;
	int		old_fd;
	int		has_pipe;

	old_fd = 0;
	has_pipe = 0;
	add_history(command);
	cmd = split_command(command);
	free(command);
	if (cmd[0])
		parser(cmd, 0, &old_fd, has_pipe);
	if (cmd)
		ft_free_split(cmd);
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
	int		old_errno;

	while (1)
	{
		old_errno = errno;
		define_signals();
		prompt = do_prompt();
		command = readline(prompt);
		free(prompt);
		errno = old_errno;
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
