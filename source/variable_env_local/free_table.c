/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 02:23:42 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/14 00:46:21 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_escapes(void)
{
	if (g_shell.escape[ESC] != NULL)
		free(g_shell.escape[ESC]);
	if (g_shell.escape[ESC_S] != NULL)
		free(g_shell.escape[ESC_S]);
}

void	free_n_exit(void)
{
	free_all(g_shell.env);
	free_all(g_shell.local);
	free_escapes();
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
