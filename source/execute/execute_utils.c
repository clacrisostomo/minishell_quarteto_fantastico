/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfico-vi <cfico-vi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 16:55:53 by cfico-vi          #+#    #+#             */
/*   Updated: 2021/12/24 16:56:27 by cfico-vi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_second_bar(char *cmd)
{
	int	i;
	int	ctn_slash;

	i = 0;
	ctn_slash = 0;
	if (cmd[0] == '.' && cmd[1] == '/')
		return (TRUE);
	while (cmd[i])
	{
		if (cmd[i] == '/')
		{
			ctn_slash++;
			if (ctn_slash >= 2)
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

int	arr_arr_size(char **splitted)
{
	int		i;

	i = 0;
	while (splitted[i] != NULL)
		i++;
	return (i);
}
