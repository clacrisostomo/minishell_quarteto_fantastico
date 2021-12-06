/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_control_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 01:54:43 by nbarreir          #+#    #+#             */
/*   Updated: 2021/11/21 02:02:55 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_string(char *command, int *idx, int *i, int q_id)
{
	int	string_count;

	string_count = 0;
	while (command[i[0]] != '\0' && i[0] < *idx)
	{
		if (command[i[0]] == ' ')
		{
			while (command[i[0]] == ' ')
				i[0]++;
			string_count++;
			i[1] = i[0];
		}
		i[0]++;
	}
	if (command[i[0]] == q_id)
		i[0]++;
	return (string_count);
}

static char	**subs_quote_ctrl_one(char *cmd, int idx, char **var)
{
	var[0] = cmd;
	var[1] = ft_substr(var[0], 0, idx);
	if (var[1] == NULL)
	{
		perror("Error: ");
		ft_free_split(var);
		return (NULL);
	}
	var[2] = ft_substr(var[0], idx + 1, ft_strlen(var[0]) - idx + 1);
	if (var[2] == NULL)
	{
		perror("Error: ");
		ft_free_split(var);
		return (NULL);
	}
	free(var[0]);
	var[0] = ft_strjoin(var[1], var[2]);
	if (var[0] == NULL)
	{
		perror("Error: ");
		var[0] = var[2];
		ft_free_split(var);
		return (NULL);
	}
	return (var);
}

static char	*subs_quote_ctrl_two(char *cmd, int idx, char **var)
{
	var[1] = ft_substr(var[0], 0, idx);
	if (var[1] == NULL)
	{
		perror("Error: ");
		var[1] = var[2];
		ft_free_split(var);
		return (NULL);
	}
	free(var[2]);
	var[2] = ft_substr(var[0], idx + 1, ft_strlen(var[0]) - idx + 1);
	if (var[0] == NULL)
	{
		perror("Error: ");
		ft_free_split(var);
		return (NULL);
	}
	cmd = ft_strjoin(var[1], var[2]);
	if (cmd == NULL)
	{
		perror("Error: ");
		ft_free_split(var);
		return (NULL);
	}
	ft_free_split(var);
	return (cmd);
}

char	*subs_quote(char *command, int idx, char q_id)
{
	char	**str_var;
	int		j;

	str_var = (char **)ft_calloc(4, sizeof(char *));
	if (str_var == NULL)
	{
		perror("Error: ");
		free(command);
		return (NULL);
	}
	j = 0;
	while (j < 4)
		str_var[j++] = NULL;
	str_var = subs_quote_ctrl_one(command, idx, str_var);
	if (str_var == NULL)
		return (NULL);
	while (str_var[0][idx] != q_id)
		idx++;
	free(str_var[1]);
	command = subs_quote_ctrl_two(command, idx, str_var);
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
