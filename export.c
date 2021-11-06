/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sants <mde-sants@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 22:36:28 by nbarreir          #+#    #+#             */
/*   Updated: 2021/10/20 22:41:28 by santsgu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int which_table_by_key(char *key)
{
	int c;
	int i;

	c = 0;
	i = 0;
	while (g_shell.env->item[c] && c <= g_shell.env->size - 1)
	{
		if (ft_strncmp(g_shell.env->item[c]->key, key, ft_strlen(key)) == 0)
			i = 1;
		c++;
	}
	/* c = 0;
	while (g_shell.hash->item[c] && c <= g_shell.hash->size - 1)
	{
		if (ft_strncmp(g_shell.hash->item[c]->key, key, ft_strlen(key)) == 0)
			i = i + 2;
		c++;
	} */
	c = 0;
	while (g_shell.local->item[c] && c <= g_shell.local->size - 1)
	{
		if (ft_strncmp(g_shell.local->item[c]->key, key, ft_strlen(key)) == 0)
			i = 2;
		c++;
	}
	return (i);
}

void change_val_by_table(t_hash_table *table, char *key, char *value, int c)
{
	if (ft_strcmp(table->item[c]->key, key) == 0)
	{
		free_item(table->item[c]);
		table->item[c] = insert_table(key, value);
		return;
	}
}

int modify_table_by_key(int table, char *key, char *value)
{
	int c;

	c = 0;
	while (g_shell.env->item[c] && c <= g_shell.env->size - 1 && table == ENV)
	{
		change_val_by_table(g_shell.env, key, value, c);
		c++;
	}
	/* c = 0;
	while (g_shell.hash->item[c] && c <= g_shell.hash->size - 1 && table == HASH)
	{
		change_val_by_table(g_shell.hash, key, value, c);
		c++;
	} */
	c = 0;
	while (g_shell.local->item[c] && c <= g_shell.local->size - 1 && table == LOCAL)
	{
		change_val_by_table(g_shell.local, key, value, c);
		c++;
	}
	return (0);
}

int loop_table_n_insert(char *key, char *value, int table)
{
	int c;

	c = 0;
	if (table == ENV)
	{
		while (g_shell.env->item[c] && c <= g_shell.env->size - 1 && ft_strcmp(g_shell.env->item[c]->key, key) != 0)
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

void insert_if_export(char *key, char *value)
{
	int t;
	int c;

	c = 0;
	t = which_table_by_key(key);
	if (t == NONE)
		loop_table_n_insert(key, value, ENV);
	if (t == ENV)
		modify_table_by_key(ENV, key, value);
	if (t == LOCAL)
	{
		while (g_shell.local->item[c] && c <= g_shell.local->size - 1)
		{
			if (ft_strncmp(g_shell.local->item[c]->key, key,
										 ft_strlen(key)) == 0)
			{
				delete_item(g_shell.local, key);
				break;
			}
			c++;
		}
		loop_table_n_insert(key, value, ENV);
	}
}

void insert_if_onlyvar(char *key, char *value)
{
	int t;

	t = which_table_by_key(key);
	if (t == NONE)
		loop_table_n_insert(key, value, LOCAL);
	if (t == ENV)
		modify_table_by_key(ENV, key, value);
	if (t == LOCAL)
		modify_table_by_key(LOCAL, key, value);
}

void expt(char **cmd, int exp)
{
	char *key;
	char *value;
	int i;
	int j;
	int t;

	i = 0;
	t = 0;
	while (cmd[i])
	{
		j = 0;
		while (ft_isalpha(cmd[i][j]) || cmd[i][j] == '_' ||
					 (ft_isdigit(cmd[i][j]) && (!ft_isdigit(cmd[i][0]))))
			j++;
		if (cmd[i][j] == '=')
		{
			key = find_key(cmd[i]);
			value = find_value(cmd[i]);
			if (exp == 1)
				insert_if_export(key, value);
			else
				insert_if_onlyvar(key, value);
			free(key);
			free(value);
		}
		else if (cmd[i][j] == '\0')
		{
			t = which_table_by_key(cmd[i]);
			value = search_hash_by_key(cmd[i]);
			if (value != NULL && t == LOCAL)
			{
				loop_table_n_insert(cmd[i], value, ENV);
				delete_item(g_shell.local, cmd[i]);
			}
		}
		i++;
	}
}