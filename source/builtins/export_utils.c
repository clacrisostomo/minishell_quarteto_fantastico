/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:11:32 by nbarreir          #+#    #+#             */
/*   Updated: 2021/11/20 20:39:38 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	which_table_by_key(char *key)
{
	int	c;
	int	i;

	c = 0;
	i = 0;
	while (g_shell.env->item[c] && c <= g_shell.env->size - 1)
	{
		if (ft_strncmp(g_shell.env->item[c]->key, key, ft_strlen(key)) == 0)
			i = 1;
		c++;
	}
	c = 0;
	while (g_shell.local->item[c] && c <= g_shell.local->size - 1)
	{
		if (ft_strncmp(g_shell.local->item[c]->key, key, ft_strlen(key)) == 0)
			i = 2;
		c++;
	}
	return (i);
}

void	change_val_by_table(t_array_table *table, char *key, char *value, int c)
{
	if (ft_strcmp(table->item[c]->key, key) == 0)
	{
		free_item(table->item[c]);
		table->item[c] = insert_table(key, value);
		return ;
	}
}

int	modify_table_by_key(int table, char *key, char *value)
{
	int	c;

	c = 0;
	while (g_shell.env->item[c] && c <= g_shell.env->size - 1 && table == ENV)
	{
		change_val_by_table(g_shell.env, key, value, c);
		c++;
	}
	c = 0;
	while (g_shell.local->item[c] && c <= g_shell.local->size - 1
		&& table == LOCAL)
	{
		change_val_by_table(g_shell.local, key, value, c);
		c++;
	}
	return (0);
}

int	loop_table_n_insert(char *key, char *value, int table)
{
	int	c;

	c = 0;
	if (table == ENV)
	{
		while (g_shell.env->item[c] && c <= g_shell.env->size - 1
			&& ft_strcmp(g_shell.env->item[c]->key, key) != 0)
			c++;
		if (c <= g_shell.env->size - 1)
		{
			g_shell.env->item[c] = insert_table(key, value);
			return (0);
		}
	}
	if (table == LOCAL)
	{
		while (g_shell.local->item[c] && c <= g_shell.local->size - 1)
			c++;
		if (c <= g_shell.local->size - 1)
		{
			g_shell.local->item[c] = insert_table(key, value);
			return (0);
		}
	}
	return (1);
}

void	error_export(char **cmd, int i)
{
	ft_putstr_fd("Minishell: export: '", 2);
	ft_putstr_fd(cmd[i], 2);
	ft_putendl_fd("': not a valid identifier", 2);
	errno = EPERM;
}
