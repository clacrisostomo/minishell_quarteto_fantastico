/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 02:23:42 by nbarreir          #+#    #+#             */
/*   Updated: 2021/11/21 02:26:00 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_all(t_array_table *table)
{
	int				i;
	t_ht_item		*item;

	i = 0;
	if (table != NULL)
	{
		if (table->item)
		{
			while (i < table->size)
			{
				item = table->item[i];
				if (item)
					free_item(item);
				i++;
			}
			free(table->item);
		}
		free(table);
	}
}

void	free_n_exit(void)
{
	free_all(g_shell.env);
	free_all(g_shell.local);
	exit(errno);
}

void	free_item(t_ht_item *item)
{
	if (item->key)
		free(item->key);
	if (item->value)
		free(item->value);
	free(item);
}
