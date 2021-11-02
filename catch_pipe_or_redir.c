/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_pipe_or_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-figu <mde-figu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 20:27:08 by mde-figu          #+#    #+#             */
/*   Updated: 2021/10/27 00:37:49 by mde-figu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	catch_pipe(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while(cmd[i][j])
		{
			if (cmd[i][j] == '|')
				return (i);
			j++;
		}
		i++;
	}
	return (0);
}

int catch_redir_output(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while(cmd[i][j])
		{
			if (cmd[i][j] == '>')
				return (i);
			j++;
		}
		i++;
	}
	return (0);
}

int catch_redir_input(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while(cmd[i][j])
		{
			if (cmd[i][j] == '<')
				return (i);
			j++;
		}
		i++;
	}
	return (0);
}

int catch_redir_append_out(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while(cmd[i][j])
		{
			if (cmd[i][j] == '>' && cmd[i][j + 1] == '>')
				return (i);
			else if (cmd[i][j] == '>' && cmd[i + 1][0] == '>')
			{
				ft_printf("Error bash: syntax error near unexpected token >");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
