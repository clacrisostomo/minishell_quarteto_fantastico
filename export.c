/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-figu <mde-figu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 22:36:28 by nbarreir          #+#    #+#             */
/*   Updated: 2021/10/13 21:59:05 by mde-figu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int which_table_by_key(char *key)
{
	int c;
	int i;

	c = 0;
	i = 0;
	while (g_shell.env->items[c] && c <= g_shell.env->size - 1)
	{
		if (ft_strncmp(g_shell.env->items[c]->key, key, ft_strlen(key)) == 0)
			i = i + 1;
		c++;
	}
	c = 0;
	while (g_shell.hash->items[c] && c <= g_shell.hash->size - 1)
	{
		if (ft_strncmp(g_shell.hash->items[c]->key, key, ft_strlen(key)) == 0)
			i = i + 2;
		c++;
	}
	while (g_shell.temp->items[c] && c <= g_shell.temp->size - 1)
	{
		if (ft_strncmp(g_shell.temp->items[c]->key, key, ft_strlen(key)) == 0)
			i = i + 3;
		c++;
	}
	return (i); //0 =nenhuma,1=env,2=hash, 3=temp, 4=env+temp, 5= hash + temp <<<<Mudar este retorno para um define
}

void change_val_by_table(t_hash_table *table, char *key, char *value, int c)
{
	if (ft_strncmp(table->items[c]->key, key, ft_strlen(key)) == 0)
	{
		free_item(table->items[c]);
		table->items[c] = insert_table(key, value);
		return ;
	}
}

int modify_table_by_key(int table, char *key, char *value)
{
	int c;

	c = 0;
	while (c <= g_shell.env->size - 1 && table == ENV)
	{
		change_val_by_table(g_shell.env, key, value, c);
		/* if (ft_strncmp(g_shell.env->items[c]->key, key, ft_strlen(key)) == 0)
			g_shell.env->items[c]->value = value;
		c++; */
		c++;
	}
	c = 0;
	while (g_shell.hash->items[c] && c <= g_shell.hash->size - 1 && table == HASH)
	{
		change_val_by_table(g_shell.hash, key, value, c);
		/* if (ft_strncmp(g_shell.hash->items[c]->key, key, ft_strlen(key)) == 0)
			g_shell.hash->items[c]->value = value;
		c++; */
		c++;
	}
	c = 0;
	while (g_shell.temp->items[c] && c <= g_shell.temp->size - 1 && table == TEMP)
	{
		change_val_by_table(g_shell.temp, key, value, c);
		/* if (ft_strncmp(g_shell.temp->items[c]->key, key, ft_strlen(key)) == 0)
			g_shell.temp->items[c]->value = value;
		c++; */
		c++;
	}
	return (0);
}

int		loop_table_n_insert(char *key, char *value, int table)
{
	int	c;
	
	c = 0;
	if(table == HASH)
	{
		while (g_shell.hash->items[c] && c <= g_shell.hash->size - 1)
			c++;
		if (c <= g_shell.hash->size - 1)
		{
			g_shell.hash->items[c] = insert_table(key, value);
			return (0);
		}
	}
	if(table == TEMP)
	{
		while (g_shell.temp->items[c] && c <= g_shell.temp->size - 1)
			c++;
		if (c <= g_shell.temp->size - 1)
		{
			g_shell.temp->items[c] = insert_table(key, value);
			return (0);
		}
	}
	return (1);
}

void		insert_if_export(char *key, char *value)
{
	//t_ht_item	*insert;
	int	t;
	int c;

	c = 0;
	t = which_table_by_key(key);
	if(t == 0)
		loop_table_n_insert(key, value, HASH);
	if (t == 1)
		modify_table_by_key(ENV, key, value);
	if (t == 2)
		modify_table_by_key(HASH, key, value);
	if (t == 3)
	{
		while (g_shell.temp->items[c] && c <= g_shell.temp->size - 1)
		{
			if (ft_strncmp(g_shell.temp->items[c]->key, key, ft_strlen(key)) == 0)
			{
				free_item(g_shell.temp->items[c]);
				break ;
			}
			c++;
		}
		loop_table_n_insert(key, value, HASH);
	}
}

void		insert_if_onlyvar(char *key, char *value)
{
	//t_ht_item	*insert;
	int	t;

	t = which_table_by_key(key);
	if (t == 0)
		loop_table_n_insert(key, value, TEMP);
	if (t == 1)
		modify_table_by_key(ENV, key, value);
	if (t == 2)
		modify_table_by_key(HASH, key, value);
	if (t == 3)
		modify_table_by_key(TEMP, key, value);
}

void expt(char **cmd, int exp)
{
	char *key;
	char *value;
	int i;
	int j;

	i = exp;
	while (cmd[i])
	{
		j = 0;
		while (ft_isalpha(cmd[i][j]) || cmd[i][j] == '_' || \
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
			//if (value)
			free(value);
		}
		else if (cmd[i][j] == '\0')
		{
			value = search_hash_by_key(cmd[i]);
			if (value)
				loop_table_n_insert(cmd[i], value, HASH);
//insert_if_export(key, value);
//loop_table_n_insert(key, value, HASH);
		}
		i++;
	}
}