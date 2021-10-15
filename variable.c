/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-figu <mde-figu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 23:00:43 by csantos-          #+#    #+#             */
/*   Updated: 2021/10/14 23:44:54 by mde-figu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int ft_isvar(char **cmd)
{
	int	j;

	j = 0;
	while (ft_isalpha(cmd[0][j]) || cmd[0][j] == '_' || \
			(ft_isdigit(cmd[0][j]) && (!ft_isdigit(cmd[0][0]))))
		j++;
	if (cmd[0][j] == '=')
		return(1);
	//else
	//	printf("%s: command not found\n", cmd[0]);
	return(0);
}
