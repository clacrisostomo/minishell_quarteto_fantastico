/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_control_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:45:35 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/07 18:45:37 by nbarreir         ###   ########.fr       */
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

static char	*delete_variable(char *command, int i, int idx)
{
	char	*str_start;
	char	*str_end;
	char	*str_ret;
	int		str_size;

	str_start = ft_substr(command, 0, idx);
	str_size = ft_strlen(command);
	str_end = ft_substr(command, i, str_size - i + 1);
	str_ret = ft_strjoin(str_start, str_end);
	free(str_start);
	free(str_end);
	return (str_ret);
}

char	**create_str_str(int size)
{
	char	**str_str;
	int		j;

	str_str = (char **)ft_calloc(size, sizeof(char *));
	if (str_str == NULL)
	{
		perror("Error: ");
		return (NULL);
	}
	j = 0;
	while (j < size)
		str_str[j++] = NULL;
	return (str_str);
}

char	*swap_var(char *command, int i, int idx)
{
	char	*val;
	char	**str_var;

	str_var = create_str_str(6);
	if (str_var == NULL)
	{
		free(command);
		return (NULL);
	}
	str_var = swap_var_ctrl_one(str_var, command, idx, i);
	if (str_var == NULL)
		return (NULL);
	val = search_array_by_key(str_var[1]);
	if (val == NULL)
		command = delete_variable(command, i, idx);
	else
	{
		str_var = swap_var_ctrl_two(str_var, val, i, idx);
		command = ft_strjoin(str_var[4], str_var[3]);
	}
	ft_free_split(str_var);
	return (command);
}
