/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 20:22:59 by csantos-          #+#    #+#             */
/*   Updated: 2021/11/20 20:39:37 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delete_item(t_array_table *table, char *key)
{
	int		c;
	char	*value;

	c = 0;
	while (table->item[c] && c <= table->size - 1)
	{
		if (ft_strcmp(table->item[c]->key, key) == 0)
		{
			while (table->item[c] && c <= table->size - 1)
			{
				free_item(table->item[c]);
				if (table->item[c + 1])
				{
					key = table->item[c + 1]->key;
					value = table->item[c + 1]->value;
					table->item[c] = insert_table(key, value);
				}
				else
					table->item[c] = NULL;
				c++;
			}
			return ;
		}
		c++;
	}
}

static void	search_key_to_unset(char *key)
{
	int	c;

	c = 0;
	while (g_shell.env->item[c] && c <= g_shell.env->size - 1)
	{
		if (ft_strncmp(g_shell.env->item[c]->key, key, ft_strlen(key)) == 0)
		{
			delete_item(g_shell.env, key);
			return ;
		}
		c++;
	}
	while (g_shell.local->item[c] && c <= g_shell.local->size - 1)
	{
		if (ft_strncmp(g_shell.local->item[c]->key, key, ft_strlen(key)) == 0)
		{
			delete_item(g_shell.local, key);
			return ;
		}
		c++;
	}
}

void	unset_(char **cmd)
{
	int	i;
	int	j;

	i = 1;
	while (cmd[i])
	{
		j = 0;
		while (ft_isalpha(cmd[i][j]) || cmd[i][j] == '_' ||
					(ft_isdigit(cmd[i][j]) && (!ft_isdigit(cmd[i][0]))))
			j++;
		if (cmd[i][j] == '=')
		{
			ft_putstr_fd("Minishell: unset: '", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			errno = EPERM;
		}
		else
		{
			search_key_to_unset(cmd[i]);
			errno = 0;
		}
		i++;
	}
}
