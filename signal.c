/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantos- <csantos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:11:02 by nbarreir          #+#    #+#             */
/*   Updated: 2021/11/03 22:15:50 by csantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	interrupt(int signal)
{
	//(void)signal;
	g_shell.status_error = 128 + signal;
	ft_printf("\n");
}

void	prompt_handler(int signal)
{
	//(void)signal;
	g_shell.status_error = 128 + signal;
	//ft_printf("\n%i", g_shell.status_error);
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
