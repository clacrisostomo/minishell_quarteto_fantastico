/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 23:00:43 by csantos-          #+#    #+#             */
/*   Updated: 2021/11/20 20:39:37 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_isvar(char **cmd)
{
	int j;
	int i;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (ft_isalpha(cmd[i][j]) || cmd[i][j] == '_' ||
					 (ft_isdigit(cmd[i][j]) && (!ft_isdigit(cmd[i][0]))))
			j++;
		if (cmd[i][j] != '=' || j == 0)
		{
			if (i > 0)
			{
				free(cmd[0]);
				cmd[0] = ft_strdup(cmd[i]);
			}
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
