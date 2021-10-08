/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_env_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 22:20:39 by nbarreir          #+#    #+#             */
/*   Updated: 2021/10/07 22:22:26 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (pwd != NULL)
		printf("%s\n", pwd);
	free(pwd);
}

int echo(char **cmd)
{
	char	*key;
	char	*val;
	int has_n;
	int i;

	has_n = 0;
	i = 1;
	if (ft_strcmp(cmd[i],"-n") == 0)
	{
		has_n = 1;
		i++;
	}
	while (cmd && cmd[i])
	{
		if (ft_strrchr(cmd[i], '$') && (ft_strcmp(cmd[i], "$\0")))
		{
			key = ft_substr(cmd[i], 1, ft_strlen(cmd[i]) - 1);
			val = search_hash_by_key(key);
			free(key);
			if (val != NULL)
				printf("%s ", val);
		}
		else
			printf("%s ", cmd[i]);
		i++;
	}
	if (has_n != 1)
		printf("\n");
	return (1);
}

void	env()
{
	int	c;

	c = 0;
	while(c <= g_shell.env->size - 1)
	{
		printf("%s=%s\n", g_shell.env->items[c]->key, g_shell.env->items[c]->value);
		c++;
	}
	c = 0;
	while(g_shell.hash->items[c] && c <= g_shell.hash->size - 1)
	{
		printf("%s=%s\n", g_shell.hash->items[c]->key, g_shell.hash->items[c]->value);
		c++;
	}
}
