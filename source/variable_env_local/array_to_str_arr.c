/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_to_str_arr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:44:49 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/07 18:44:51 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**array_to_str_arr(t_array_table *n_env)
{
	int		i;
	int		j;
	char	**ret;
	char	*str_start;

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
