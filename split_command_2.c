/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfico-vi <cfico-vi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:20:42 by cfico-vi          #+#    #+#             */
/*   Updated: 2021/11/03 16:48:09 by cfico-vi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*expand_quote_var(char *command, int *idx, int q_id)
{
	int		i;

	i = *idx;
	while (command[++i] != q_id)
	{
		if (command[i] == '$' && command[i + 1] != S_QUOTE)
			command = expand_var(command, i);
	}
	return (command);
}

int	count_string(char *command, int *idx, int *i, int q_id)
{
	int		string_count;

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

char	*subs_quote(char *command, int idx, char q_id)
{
	char		*str_start;
	char		*str_end;

	str_start = ft_substr(command, 0, idx);
	str_end = ft_substr(command, idx + 1, ft_strlen(command) - idx + 1);
	free(command);
	command = ft_strjoin(str_start, str_end);
	free(str_start);
	free(str_end);
	while (command[idx] != q_id)
		idx++;
	str_start = ft_substr(command, 0, idx);
	str_end = ft_substr(command, idx + 1, ft_strlen(command) - idx + 1);
	free(command);
	command = ft_strjoin(str_start, str_end);
	free(str_start);
	free(str_end);
	return (command);
}

static t_joker_m	*add_joker_list(t_joker_m *space, t_joker_m *new_joker)
{
	t_joker_m	*tmp;

	new_joker = ft_calloc(1, sizeof(t_joker_m));
	tmp = space;
	while (tmp->next_jok != NULL)
		tmp = tmp->next_jok;
	tmp->next_jok = new_joker;
	return (new_joker);
}

void	put_jokers_c(char *command, t_joker_m *joker_list, int *i, int q_id)
{
	t_joker_m	*new_joker;

	new_joker = NULL;
	new_joker = add_joker_list(joker_list, new_joker);
	new_joker->id = ft_calloc(i[4], sizeof(int));
	new_joker->id_size = i[4] - 1;
	new_joker->split_c = i[3];
	i[0] = 0;
	i[4] = i[2] + 1;
	while (command[i[4]] != q_id)
	{
		if (command[i[4]] == ' ')
		{
			command[i[4]] = JOK_C;
			if (i[3] == 0)
				new_joker->id[i[0]] = i[4] - 1;
			else
				new_joker->id[i[0]] = i[4] - i[1] - 1;
			i[0]++;
		}
		i[4]++;
	}
}
