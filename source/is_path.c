/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 21:51:19 by mde-figu          #+#    #+#             */
/*   Updated: 2021/11/20 20:39:37 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_path(char **cmd, char **n_env)
{
	int c;

	c = 0;
	if (cmd[0][0] == '/')
	{
		return (1);
	}
	while (cmd[0][c])
	{
		if (cmd[0][c] == '/')
		{
			if (cmd[0][c] + 1 == '\0')
				execve(cmd[0], cmd, n_env);
		}
		c++;
	}
	return (0);
}
