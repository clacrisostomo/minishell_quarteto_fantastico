/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantos- <csantos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:20:42 by cfico-vi          #+#    #+#             */
/*   Updated: 2021/11/03 22:45:20 by csantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*swap_var(char *command, int i, int idx)
{
	char		*key;
	char		*val;
	char		*str_start;
	char		*str_end;
	char		*str_start_val;

	key = ft_substr(command, idx + 1, i - idx - 1);
	val = search_hash_by_key(key);
	free(key);
	str_start = ft_substr(command, 0, idx);
	str_end = ft_substr(command, i, ft_strlen(command) - i);
	free(command);
	if (val == NULL)
		str_start_val = ft_strjoin(str_start, "");
	else
		str_start_val = ft_strjoin(str_start, val);
	free(str_start);
	command = ft_strjoin(str_start_val, str_end);
	free(str_end);
	free(str_start_val);
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
		command = expand_quote_var(command, idx, q_id);
	while (command[++(*idx)] != q_id)
	{
		if (command[*idx] == ' ')
			i[4]++;
	}
	(*idx) = (*idx) - 3;
	if (i[4] > 0)
		put_jokers_c(command, joker_list, i, q_id);
	command = subs_quote(command, i[2], q_id);
	return (command);
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
				command = expand_error(command, i);
			else if (command[i + 1])
				command = expand_var(command, i--);
		}
		else if (command[i] == D_QUOTE)
			command = check_second_quote(command, &i, D_QUOTE, joker_list);
		else if (command[i] == S_QUOTE)
			command = check_second_quote(command, &i, S_QUOTE, joker_list);
		else if (command[i] == INPUT || command[i] == PIPE
			|| command[i] == OUTPUT)
			command = set_space_for_redir(command, &i);
		i++;
	}
	return (command);
}
