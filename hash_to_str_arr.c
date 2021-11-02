/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_to_str_arr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirkios <mirkios@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 22:58:09 by cfico-vi          #+#    #+#             */
/*   Updated: 2021/10/24 23:110:02 by mirkios          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	**hash_to_str_arr(t_hash_table *n_env)
{
	int		i;
	int		j;
	char	**ret;
	char	*str_start;

	j = 0;
	i = 0;
	while(n_env->item[j])
		j++;
	ret = (char **)malloc((j + 1) * sizeof(char *));
	while(n_env->item[i])
	{
		str_start = ft_strjoin(n_env->item[i]->key, "=");
		ret[i] = ft_strjoin(str_start, n_env->item[i]->value);
		free(str_start);
		i++;
	}
	ret[i] = NULL;
	printf(" O valor de I: %i\n", i);
	return (ret);
}
