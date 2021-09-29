
#include "minishell.h"

t_ht_item	*insert_table(char *key, char *value)
{
	t_ht_item* new_item;
	
	new_item = create_hash_item(key, value);
	return (new_item);
}

void	free_item(t_ht_item **items)
{
    //free((*items)->key);
    //free((*items)->value);
    free(items);
}
void	free_table(t_hash_table *table)
{
    int i;
    t_ht_item *item;

    i = 0;
    while (i++ < g_shell.hash->size - 1)
    {
        item = table->items[i];
        if (item != NULL)
            free(item);
    }
    free(table->items);
   // free(table);
}

void	create_hash_table(int size)
{
	int	i;

	i = 0;
	g_shell.hash = (t_hash_table *)malloc(sizeof(t_hash_table));
	g_shell.hash->size = size;
	g_shell.hash->count = 0;
	g_shell.hash->items = (t_ht_item**) ft_calloc(g_shell.hash->size, sizeof(t_ht_item*));
	while( i++ < g_shell.hash->size - 1)
	{
		g_shell.hash->items[i] = NULL;
	}
}

t_ht_item	*create_hash_item(char* key, char* value)
{
	t_ht_item *new;
	
	new = (t_ht_item*) ft_calloc(sizeof(t_ht_item), 1);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	return (new);
}

/* void	create(char* key, char* value)
{
	g_shell.hash->items = (t_ht_item**) ft_calloc(sizeof(t_ht_item*), 1);
	g_shell.hash->items->key = ft_strdup(key);
	g_shell.hash->items->value = ft_strdup(value);
} */

char	*find_value(char *line)
{
	char	*value;
	int i;
	int j;

	i = 0;
	while(line[i] != '=')
		i++;
	j = i;
	while(line[j])
		j++;
	value = ft_substr(line, i, j);
	return (value);
}

char	*find_key(char *line)
{
	char	*key;
	int i;

	i = 0;
	while(line[i] != '=')
		i++;
	key = ft_substr(line, 0, i);
	return (key);
}

void	envp_to_hash(char **envp)
{
	char	*key;
	char	*value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while(envp[i]) //não sei talvez sim
		i++;
	create_hash_table(i);
	while (j < i)
	{
		key = find_key(envp[j]);
		value = find_value(envp[j]);
		g_shell.hash->items[j] = insert_table(key, value);
		j++;
		free(key);
		free(value);
	}
}
