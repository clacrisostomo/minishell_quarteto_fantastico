/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_control_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 01:41:27 by nbarreir          #+#    #+#             */
/*   Updated: 2021/11/21 01:53:29 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**swap_var_ctrl_one(char **str_var, char *command, int idx, int i)
{
	str_var[0] = command;
	str_var[1] = ft_substr(str_var[0], idx + 1, i - idx - 1);
	if (str_var[1] == NULL)
	{
		perror("Error: ");
		ft_free_split(str_var);
		return (NULL);
	}
	return (str_var);
}

static char	**swap_var_ctrl_two(char **str_var, char *val, int i, int idx)
{
	str_var[2] = ft_substr(str_var[0], 0, idx);
	if (str_var[2] == NULL)
	{
		perror("Error: ");
		ft_free_split(str_var);
		return (NULL);
	}
	str_var[3] = ft_substr(str_var[0], i, ft_strlen(str_var[0]) - i);
	if (str_var[3] == NULL)
	{
		perror("Error: ");
		ft_free_split(str_var);
		return (NULL);
	}
	if (val == NULL)
		str_var[4] = ft_strjoin(str_var[2], "");
	else
		str_var[4] = ft_strjoin(str_var[2], val);
	if (str_var[4] == NULL)
	{
		perror("Error: ");
		ft_free_split(str_var);
		return (NULL);
	}
	return (str_var);
}

static char	*swap_var(char *command, int i, int idx)
{
	char	*val;
	char	**str_var;
	int		j;

	str_var = (char **)ft_calloc(6, sizeof(char *));
	if (str_var == NULL)
	{
		perror("Error: ");
		free(command);
		return (NULL);
	}
	j = 0;
	while (j < 6)
		str_var[j++] = NULL;
	str_var = swap_var_ctrl_one(str_var, command, idx, i);
	if (str_var == NULL)
		return (NULL);
	val = search_hash_by_key(str_var[1]);
	str_var = swap_var_ctrl_two(str_var, val, i, idx);
	command = ft_strjoin(str_var[4], str_var[3]);
	ft_free_split(str_var);
	return (command);
}

char	*expand_var(char *command, int idx)
{
	int	i;

	i = idx + 1;
	while (command[i] != ' ' && command[i] != D_QUOTE && command[i] != S_QUOTE
		&& command[i] != '=' && (command[i]))
		i++;
	command = swap_var(command, i, idx);
	return (command);
}
