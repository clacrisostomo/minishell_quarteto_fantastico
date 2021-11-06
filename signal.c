/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-figu <mde-figu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:11:02 by nbarreir          #+#    #+#             */
/*   Updated: 2021/11/06 00:21:04 by mde-figu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	interrupt(int signal)
{
	errno = 128 + signal;
	ft_printf("\n");
}

void	prompt_handler(int signal)
{
	errno = 128 + signal;
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

/* 
g_shell.status_error: 
126 -> Permission Denied
127 -> Command not found
128 + signal -> Kill signal status
*/
