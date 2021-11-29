/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 23:00:43 by csantos-          #+#    #+#             */
/*   Updated: 2021/11/21 02:26:08 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isvar(char **cmd)
{
	int	j;
	int	i;

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

char	*find_value(char *line)
{
	char	*value;
	int		i;
	int		j;

	i = 0;
	while (line[i] != '=')
		i++;
	j = i;
	while (line[j])
		j++;
	value = ft_substr(line, i + 1, j);
	return (value);
}

char	*find_key(char *line)
{
	char	*key;
	int		i;

	i = 0;
	while (line[i] != '=')
		i++;
	key = ft_substr(line, 0, i);
	return (key);
}
