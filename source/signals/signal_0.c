/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfico-vi <cfico-vi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 13:31:46 by cfico-vi          #+#    #+#             */
/*   Updated: 2021/12/24 15:54:31 by cfico-vi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_interactive_handler(int signal)
{
	(void) signal;
	errno = 130;
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	define_interactive_signals(void)
{
	signal(SIGINT, sigint_interactive_handler);
	signal(SIGQUIT, SIG_IGN);
}

static void	sigint_child_handler(int signal)
{
	errno = 128 + signal;
	ft_putchar_fd('\n', STDOUT);
}

static void	sigquit_child_handler(int signal)
{
	(void) signal;
	errno = 131;
	ft_printf("Quit (core dumped)\n");
}

void	define_child_signals(void)
{
	signal(SIGINT, sigint_child_handler);
	signal(SIGQUIT, sigquit_child_handler);
}
