/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdefic-vifigu <mdefic-vifigu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 21:28:08 by mde-figu          #+#    #+#             */
/*   Updated: 2021/10/20 23:30:16 by cfimde-vifigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*swap_var(char *command, int i, int idx)
{
	char	*key;
	char	*val;
	char	*str_start;
	char	*str_end;
	char	*str_start_val;

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
	//ft_printf("|%s|\n", command);
	return (command);
}

static char	*expand_var(char *command, int idx)
{
	int		i;

	i = idx + 1;
	while (command[i] != ' ' && command[i] != D_QUOTE
		&& command[i] != S_QUOTE && (command[i]))
		i++;
	command = swap_var(command, i, idx);
	return (command);
}

static char	*expand_quote_var(char *command, int *idx, int q_id)
{
	int		i;

	i = *idx;
	while (command[++i] != q_id)
	{
		if (command[i] == '$')
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

static char	*subs_quote(char *command, int idx, char q_id)
{
	char	*str_start;
	char	*str_end;

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

static t_joker_m	*add_joker_list(t_joker_m *space, t_joker_m	*new_joker)
{
	t_joker_m	*tmp;

	new_joker = ft_calloc(1, sizeof(t_joker_m));
	tmp = space;
	while (tmp->next_jok != NULL)
		tmp = tmp->next_jok;
	tmp->next_jok = new_joker;
	return (new_joker);
}

static void	put_jokers_c(char *command, t_joker_m *joker_list, int *i, int q_id)
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

static char	*treat_quotes(char *command, int *idx,
	int q_id, t_joker_m *joker_list)
{
	int			i[5];

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

char	*check_second_quote(char *command, int *idx,
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
			if (command[i + 1])
				command = expand_var(command, i--);
		}
		else if (command[i] == D_QUOTE)
			command = check_second_quote(command, &i, D_QUOTE, joker_list);
		else if (command[i] == S_QUOTE)
			command = check_second_quote(command, &i, S_QUOTE, joker_list);
		i++;
	}
	return (command);
}

static char	**swap_spaces(char **splitted,
		t_joker_m *lst, t_joker_m *tmp)
{
	while (lst->next_jok != NULL)
	{
		while (lst->id_size >= 0)
		{
			splitted[lst->split_c][lst->id[lst->id_size]] = ' ';
			lst->id_size--;
		}
		free(lst->id);
		tmp = lst->next_jok;
		free(lst);
		lst = tmp;
	}
	while (lst->id_size >= 0)
	{
		splitted[lst->split_c][lst->id[lst->id_size]] = ' ';
		lst->id_size--;
	}
	free(lst->id);
	free(lst);
	return (splitted);
}

static char	**unchange_jok_c(char **splitted, t_joker_m *lst)
{
	t_joker_m		*tmp;

	tmp = NULL;
	if (lst->next_jok != NULL)
		tmp = lst->next_jok;
	free(lst);
	lst = tmp;
	if (lst == NULL)
		return (splitted);
	return (swap_spaces(splitted, lst, tmp));
}

char	**split_command(char *command)
{
	t_joker_m	*joker_list;
	char		**splitted;

	command = ft_strdup(command);
	joker_list = ft_calloc(1, sizeof(t_joker_m));
	command = treat_command(command, joker_list);
	splitted = ft_split(command, ' ');
	splitted = unchange_jok_c(splitted, joker_list);
	free(command);
	return (splitted);
}
