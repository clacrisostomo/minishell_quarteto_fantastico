/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_by_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfico-vi <cfico-vi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 22:18:04 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/23 13:04:29 by cfico-vi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_array_by_key(char *key)
{
	int	c;

	c = 0;
	if (key[0] != '\0')
	{
		while (g_shell.env->item[c] && c <= g_shell.env->size - 1)
		{
			if (ft_strncmp(g_shell.env->item[c]->key, key, ft_strlen(key)) == 0)
				return (g_shell.env->item[c]->value);
			c++;
		}
		c = 0;
		while (g_shell.local->item[c] && c <= g_shell.local->size - 1)
		{
			if (!ft_strncmp(g_shell.local->item[c]->key, key, ft_strlen(key)))
				return (g_shell.local->item[c]->value);
			c++;
		}
	}
	return (NULL);
}

void	modify_array_by_key(char *key, char *new_val)
{
	int	c;

	c = 0;
	while (g_shell.env->item[c] && c <= g_shell.env->size - 1)
	{
		if (ft_strncmp(g_shell.env->item[c]->key, key, ft_strlen(key)) == 0)
		{
			free_item(g_shell.env->item[c]);
			g_shell.env->item[c] = insert_table(key, new_val);
			return ;
		}
		c++;
	}
	c = 0;
	while (g_shell.local->item[c] && c <= g_shell.local->size - 1)
	{
		if (ft_strncmp(g_shell.local->item[c]->key, key, ft_strlen(key)) == 0)
		{
			free_item(g_shell.local->item[c]);
			g_shell.local->item[c] = insert_table(key, new_val);
			return ;
		}
		c++;
	}
}
