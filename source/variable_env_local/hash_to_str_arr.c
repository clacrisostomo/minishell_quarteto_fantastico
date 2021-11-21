/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_to_str_arr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:24:49 by cfico-vi          #+#    #+#             */
/*   Updated: 2021/11/20 20:39:37 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **hash_to_str_arr(t_hash_table *n_env)
{
	int i;
	int j;
	char **ret;
	char *str_start;

	j = 0;
	i = 0;
	while (n_env->item[j])
		j++;
	ret = (char **)malloc((j + 1) * sizeof(char *));
	while (n_env->item[i])
	{
		str_start = ft_strjoin(n_env->item[i]->key, "=");
		ret[i] = ft_strjoin(str_start, n_env->item[i]->value);
		free(str_start);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
