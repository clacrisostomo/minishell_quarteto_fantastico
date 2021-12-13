/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_only.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:46:45 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/07 18:46:47 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sort_alpha(char **str)
{
	int		x;
	int		y;
	char	*aux;

	x = 0;
	while (str[x])
	{
		y = 0;
		while (str[y])
		{
			if (ft_strcmp(str[x], str[y]) < 0)
			{
				aux = str[x];
				str[x] = str[y];
				str[y] = aux;
			}
			y++;
		}
		x++;
	}
}

char	*put_quotes(t_ht_item *new_env)
{
	char	*exp_env;
	char	*new_key;
	char	*new_val;

	if (new_env->value)
	{
		new_key = ft_strjoin(new_env->key, "=");
		exp_env = ft_strjoin("\"", new_env->value);
		new_val = ft_strjoin(exp_env, "\"");
		free(exp_env);
		exp_env = ft_strjoin(new_key, new_val);
		free(new_key);
		free(new_val);
	}
	else
		exp_env = ft_strdup(new_env->key);
	return (exp_env);
}

char	**env_with_quotes(void)
{
	int					i;
	char				**env;
	t_ht_item			*temp;

	i = 0;
	while (g_shell.env->item[i])
		i++;
	env = (char **)ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (g_shell.env->item[i] && i <= g_shell.env->size - 1)
	{
		temp = g_shell.env->item[i];
		env[i] = put_quotes(temp);
		i++;
	}
	return (env);
}

void	print_export_env(char **array, int fd)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		ft_putendl_fd(array[i], fd);
		i++;
	}
}

void	export_only(void)
{
	char	**export_env;
	char	*temp;
	int		c;

	c = 0;
	export_env = env_with_quotes();
	sort_alpha(export_env);
	while (export_env[c])
	{
		temp = ft_strjoin("declare -x ", export_env[c]);
		free(export_env[c]);
		export_env[c] = temp;
		c++;
	}
	print_export_env(export_env, STDOUT_FILENO);
	ft_free_split(export_env);
}
