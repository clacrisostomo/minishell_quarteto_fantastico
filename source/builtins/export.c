/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 01:39:00 by nbarreir          #+#    #+#             */
/*   Updated: 2021/11/20 20:39:38 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	insert_if_export(char *key, char *value)
{
	int	t;
	int	c;

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
				break ;
			}
			c++;
		}
		loop_table_n_insert(key, value, ENV);
	}
}

void	insert_if_onlyvar(char *key, char *value)
{
	int	t;

	t = which_table_by_key(key);
	if (t == NONE)
		loop_table_n_insert(key, value, LOCAL);
	if (t == ENV)
		modify_table_by_key(ENV, key, value);
	if (t == LOCAL)
		modify_table_by_key(LOCAL, key, value);
}

void	if_have_key(char **cmd, int i, int exp)
{
	char	*key;
	char	*value;

	key = find_key(cmd[i]);
	value = find_value(cmd[i]);
	if (exp == 1)
		insert_if_export(key, value);
	else
		insert_if_onlyvar(key, value);
	free(key);
	free(value);
}

void	if_have_only_value(char **cmd, int i)
{
	int		t;
	char	*value;

	t = which_table_by_key(cmd[i]);
	value = search_array_by_key(cmd[i]);
	if (value != NULL && t == LOCAL)
	{
		loop_table_n_insert(cmd[i], value, ENV);
		delete_item(g_shell.local, cmd[i]);
	}
}

void	expt(char **cmd, int exp)
{
	int	i;
	int	j;

	i = 0;
	if (!cmd[exp] && exp == 1)
		export_only();
	else
	{
		while (cmd[i])
		{
			j = 0;
			while (ft_isalpha(cmd[i][j]) || cmd[i][j] == '_' ||
						(ft_isdigit(cmd[i][j]) && (!ft_isdigit(cmd[i][0]))))
				j++;
			if (cmd[i][j] == '=')
				if_have_key(cmd, i, exp);
			else if (cmd[i][j] == '\0')
				if_have_only_value(cmd, i);
			else
				error_export(cmd, i);
			i++;
		}
	}
}
