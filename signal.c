/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfico-vi <cfico-vi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:11:02 by nbarreir          #+#    #+#             */
/*   Updated: 2021/11/03 15:19:10 by cfico-vi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	interrupt(int signal)
{
	(void)signal;
	g_shell.status_error = 130;
	ft_printf("\n");
}

void	prompt_handler(int signal)
{
	(void)signal;
	g_shell.status_error = 130;
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	define_signals(void)
{
	signal(SIGINT, prompt_handler);
	signal(SIGQUIT, SIG_IGN);
}

//error = 130 -> 130 - comando finalizado devido à pressão do Ctrl-C, 130-128 = 2 (SIGINT)
//error = 13 -> kill?
