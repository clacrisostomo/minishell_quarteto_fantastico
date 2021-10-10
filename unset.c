/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantos- <csantos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 20:22:59 by csantos-          #+#    #+#             */
/*   Updated: 2021/10/10 00:43:03 by csantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/* define CAPACITY 50000 // Size of the Hash Table
 
unsigned long hash_function(char* str) {
    unsigned long i = 0;
    for (int j=0; str[j]; j++)
        i += str[j];
    return i % CAPACITY;
}
 */
 
/* void	free_var(void *var)
{
	if (((t_ht_item *)var)->key)
		free(((t_ht_item *)var)->key);
	if (((t_ht_item *)var)->value)
		free(((t_ht_item *)var)->value);
	if (var)
		free(var);
}

t_list	*search_item_in_lst(t_hash_table *table, char *key)
{
	t_list	*lst;
	t_ht_item *item;

	lst = table;
	while (lst)
	{
		item = (t_ht_item *)lst->content;
		if (!(ft_strcmp(item->key, key)))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	del_item(t_hash_table *table, char *key)
{
	t_list *lst;
	t_list *next;

	lst = search_item_in_lst(table, key);
	if (!lst)
		return ;
	next = lst->next;
	lst->next = NULL;
	lst = next;
	table->size--;
	ft_lstclear(&lst, free_var);
} */

void	delete_item(t_hash_table *table, char *key)
{
	int	c;
	char *value;
	//int i;

	c = 0;
	while(table->items[c] && c <= table->size - 1)
	{
		if (ft_strncmp(table->items[c]->key, key, ft_strlen(key)) == 0)
		{
			while (table->items[c] && c <= table->size - 1)
			{
				free_item(table->items[c]);
				if (table->items[c + 1])
				{
					key = table->items[c + 1]->key;
					value = table->items[c + 1]->value;
					table->items[c] = insert_table(key, value);
					//free(key);
					//free(value);
				}
				else
					table->items[c] = NULL;
				c++;
			}
			return ;
		}
		c++;
	}
}

void	search_key_to_unset(char *key)
{
	int	c;

	c = 0;
	while(c <= g_shell.env->size - 1)
	{
		if (ft_strncmp(g_shell.env->items[c]->key, key, ft_strlen(key)) == 0)
		{
			delete_item(g_shell.env, key);
			//g_shell.env->size--;
			return ;
		}
		c++;
	}
	c = 0;
	while(g_shell.hash->items[c] && c <= g_shell.hash->size - 1)
	{
		if (ft_strncmp(g_shell.hash->items[c]->key, key, ft_strlen(key)) == 0)
		{
			delete_item(g_shell.hash, key);
			return ;
		}
		c++;
	}
	while(g_shell.temp->items[c] && c <= g_shell.temp->size - 1)
	{
		if (ft_strncmp(g_shell.temp->items[c]->key, key, ft_strlen(key)) == 0)
		{
			delete_item(g_shell.temp, key);
			return ;
		}
		c++;
	}
}

void	unset_(char **cmd)
{
	int i;
	int j;

	i = 1;
	while (cmd[i])
	{
		j = 0;
		while (ft_isalpha(cmd[i][j]) || cmd[i][j] == '_' || \
				(ft_isdigit(cmd[i][j]) && (!ft_isdigit(cmd[i][0]))))
			j++;
		if (cmd[i][j] == '=')
		{
			ft_putstr_fd("Minishell: unset: '", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
		}
		else
			search_key_to_unset(cmd[i]);
		i++;
	}
}