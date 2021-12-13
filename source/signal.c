/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:11:02 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/10 04:37:39 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	interrupt(int signal)
{
	errno = 128 + signal;
	ft_printf("\n");
}

void	prompt_handler(int signal)
{
	if (isatty(STDIN))
	{
		errno = 128 + signal;
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	define_signals(void)
{
	signal(SIGINT, prompt_handler);
	signal(SIGQUIT, SIG_IGN);
}

static void	exec_handler(int signal)
{
	if (signal == SIGINT)
	{
		errno = 130;
		ft_printf("\n");
	}
	if (signal == SIGQUIT)
	{
		errno = 131;
		ft_putendl_fd("Quit (core dumped)", 2);
	}
}

void	define_signals_exec(void)
{
	signal(SIGINT, exec_handler);
	signal(SIGQUIT, exec_handler);
}
