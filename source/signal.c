/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfico-vi <cfico-vi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 13:31:46 by cfico-vi          #+#    #+#             */
/*   Updated: 2021/12/23 14:12:59 by cfico-vi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	interrupt(int signal)
{
	errno = 128 + signal;
	ft_putchar_fd('\n', STDOUT);
}

void	sigint_handler(int signal)
{
	if (isatty(STDIN))
	{
		errno = 128 + signal;
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		g_shell.status_error = 130;
		ft_putchar_fd('\n', STDOUT);
	}
}

void	sigquit_handler(int signal)
{
	(void) signal;
	if (!isatty(STDIN))
	{
		g_shell.status_error = 131;
		ft_putendl_fd("Quit (core dumped)", 2);
	}
}

void	define_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}

void	sighandler_in_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		exit(130);
	}
}
