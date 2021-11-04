/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantos- <csantos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 23:40:05 by csantos-          #+#    #+#             */
/*   Updated: 2021/11/03 23:17:26 by csantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_ht_item	*insert_table(char *key, char *value)
{
	t_ht_item	*new_item;

	new_item = create_hash_item(key, value);
	return (new_item);
}

void	free_n_exit(t_hash_table *table)
{
	int			i;
	t_ht_item	*item;

	i = 0;
	while (i < table->size)
	{
		item = table->item[i];
		if (item)
			free_item(item);
		i++;
	}
	exit (EXIT_SUCCESS);
}

void	free_item(t_ht_item *item)
{
	free(item->key);
	free(item->value);
	free(item);
}

t_hash_table	*create_hash_table(int size)
{
	t_hash_table	*hashtable;
	int				i;

	i = 0;
	hashtable = (t_hash_table *)malloc(sizeof(t_hash_table));
	hashtable->size = size;
	hashtable->count = 0;
	hashtable->item = (t_ht_item **) ft_calloc(hashtable->size,
			sizeof(t_ht_item*));
	while (i++ < hashtable->size - 1)
	{
		hashtable->item[i] = NULL;
	}
	return (hashtable);
}

t_ht_item	*create_hash_item(char *key, char *value)
{
	t_ht_item	*new;

	new = (t_ht_item *) ft_calloc(sizeof(t_ht_item), 1);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	return (new);
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

t_hash_table	*envp_to_hash(char **envp)
{
	t_hash_table	*table;
	char			*key;
	char			*value;
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (envp[i])
		i++;
	table = create_hash_table(i + 60);
	while (j < i)
	{
		key = find_key(envp[j]);
		value = find_value(envp[j]);
		table->item[j] = insert_table(key, value);
		j++;
		free(key);
		free(value);
	}
	return (table);
}
