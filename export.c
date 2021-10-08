/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 22:36:28 by nbarreir          #+#    #+#             */
/*   Updated: 2021/10/08 00:24:24 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/* void	insert_new_item(t_hash_table *table, char *new_key, char *new_val)
{
	int	i;
} */

static int which_table_by_key(char *key)
{
	int c;
	int i;

	c = 0;
	i = 0;
	while (c <= g_shell.env->size - 1)
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
	return (i); //0 =nenhuma,1=env,2=hash, 3=temp, 4=env+temp, 5= hash + temp
}

void export(char **cmd)
{
	char *key;
	char *value;
	int i;
	int j;
	int		t;

	i = 1;
	t = 0;
	while (cmd[i])
	{
		j = 0;
		while ((cmd[i][j] <= 90 && cmd[i][j] >= 65) || ft_isdigit(cmd[i][j]))
			j++;
		printf("%i\n", j);
		if (cmd[i][j] == '=') // tem key e valor!!
		{
			key = find_key(cmd[i]);
			value = find_value(cmd[i]);
			printf("%s\n", key);
			printf("%s\n", value);
			//modify env/hash->
			//if temp -> free
			//insert -> hash
			t = which_table_by_key(key); //!!!!!!!!!<<< PARAMOS AQUI
			/*if(t == 0)
				insert na hash
			if(t == 1)
				modify na env
			if(t == 2)
				modify na hash
			if(t == 3)
				free temp
				inserir na hash
			if(t == 4)
				free temp
				modify na env
			if(t == 5)
				free temp
				moficy na hash */
			free(key);
			free(value);
		}
		else if (cmd[i][j] == '\0') // esse tem key mas nao tem valor!
		{
			key = cmd[i];
			printf("%s\n", key);
			//if temp -> free
			//insert -> no hash
		}
		i++;
	}
	t = t + 1; //Apagar isso depois, usamos soh para deixar compilando, assim que usar o t de fato apagar essa linha
}
