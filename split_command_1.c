/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfico-vi <cfico-vi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:20:42 by cfico-vi          #+#    #+#             */
/*   Updated: 2021/11/06 13:14:35 by cfico-vi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*swap_var(char *command, int i, int idx)
{
	char	*val;
	char 	**str_var;
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
	str_var[0] = command;
	str_var[1] = ft_substr(str_var[0], idx + 1, i - idx - 1);
	if (str_var[1] == NULL)
	{
		perror("Error: ");
		ft_free_split(str_var);
		return (NULL);
	}
	val = search_hash_by_key(str_var[1]);
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
	command = ft_strjoin(str_var[4], str_var[3]);
	ft_free_split(str_var);
	return (command);
}

char	*expand_var(char *command, int idx)
{
	int		i;

	i = idx + 1;
	while (command[i] != ' ' && command[i] != D_QUOTE
		&& command[i] != S_QUOTE && command[i] != '=' && (command[i]))
		i++;
	command = swap_var(command, i, idx);
	return (command);
}

static char	*treat_quotes(char *command, int *idx,
												int q_id, t_joker_m *joker_list)
{
	int		i[5];

	i[0] = 0;
	i[4] = 0;
	i[3] = count_string(command, idx, i, q_id);
	i[2] = *idx;
	if (q_id == D_QUOTE)
	{
		command = expand_quote_var(command, idx, q_id);
		if (command == NULL)
		{
			free_joker_list(joker_list);
			free_n_exit();
		}
	}
	while (command[++(*idx)] != q_id)
	{
		if (command[*idx] == ' ')
			i[4]++;
	}
	(*idx) = (*idx) - 3;
	if (i[4] > 0)
		put_jokers_c(command, joker_list, i, q_id);
	command = subs_quote(command, i[2], q_id);
	if (command == NULL)
	{
		free_joker_list(joker_list);
		free_n_exit();
	}	return (command);
}

static char	*check_second_quote(char *command, int *idx,
												int q_id, t_joker_m *joker_list)
{
	int		j;

	j = *idx;
	while (command[j++] != '\0')
	{
		if (command[j] == q_id)
		{
			command = treat_quotes(command, idx, q_id, joker_list);
			break ;
		}
	}
	return (command);
}

char	*treat_command(char *command, t_joker_m *joker_list)
{
	int		i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '$')
		{
			if (command[i + 1] == D_QUOTE || command[i + 1] == S_QUOTE)
				command[i] = ' ';
			else if (command[i + 1] == '?')
			{
				command = expand_error(command, i);
				if (command == NULL)
				{
					free_joker_list(joker_list);
					free_n_exit();
				}
			}
			else if (command[i + 1])
			{
				command = expand_var(command, i--);
				if (command == NULL)
				{
					free_joker_list(joker_list);
					free_n_exit();
				}
			}
		}
		else if (command[i] == D_QUOTE)
			command = check_second_quote(command, &i, D_QUOTE, joker_list);
		else if (command[i] == S_QUOTE)
			command = check_second_quote(command, &i, S_QUOTE, joker_list);
		else if (command[i] == INPUT || command[i] == PIPE
			|| command[i] == OUTPUT)
		{
			command = set_space_for_redir(command, &i);
			if (command == NULL)
			{
				free_joker_list(joker_list);
				free_n_exit();
			}
		}
		i++;
	}
	return (command);
}
