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
	int     i;
    int     j;
    char	**ret;
    char    *key;
    char    *val;

    j = 0;
    i = 0;
    while(n_env->item[j])
        j++;
    ret = (char **)malloc(j * sizeof(char *));
    while(n_env->item[i])
    {
        key = n_env->item[i]->key;
        val = n_env->item[i]->value;
        ret[i] = ft_strjoin(ft_strjoin(key, "="), val);
        i++;
    }
    return (ret);
}
