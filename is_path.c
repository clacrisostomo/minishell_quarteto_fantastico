/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-figu <mde-figu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 21:51:19 by mde-figu          #+#    #+#             */
/*   Updated: 2021/10/19 23:26:27 by mde-figu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	is_path(char **cmd, char **envp)
{
	int	c;
	
	c = 0;

	if (cmd[0][0] == '/')
	{
		return (1);
	}
	while(cmd[0][c])
	{
		if (cmd[0][c] == '/')
		{
			if (cmd[0][c] + 1 == '\0' )
				execve(cmd[0], cmd, envp);
		}
		c++;
	}
	return (0);
}
