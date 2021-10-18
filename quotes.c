/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfico-vi <cfico-vi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 21:28:08 by mde-figu          #+#    #+#             */
/*   Updated: 2021/10/17 22:55:45 by cfico-vi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*swap_var(char *command, int *i)
{
	char	*key;
	char	*val;
	char	*str_start;
	char	*str_end;
	char	*str_start_val;

	//ft_printf("command = |%s|, i[0] = %d, i[1] = %d\n", command, i[0], i[1]);
	key = ft_substr(command, i[0] + 1, i[1] - i[0] - 1);
	val = search_hash_by_key(key);
	//ft_printf("val = |%s|\n", val);
	free(key);
	str_start = ft_substr(command, 0, i[0]);
	//ft_printf("str_start = |%s|\n", str_start);
	str_end = ft_substr(command, i[1], ft_strlen(command) - i[1]);
	//ft_printf("str_end = |%s|\n", str_end);
	free(command);
	str_start_val = ft_strjoin(str_start, val);
	//ft_printf("str_start_val = |%s|\n", str_start_val);
	free(str_start);
	command = ft_strjoin(str_start_val, str_end);
	//ft_printf("command = |%s|\n", command);
	free(str_end);
	free(str_start_val);
	return (command);
}

static char	*expand_var(char *command)
{
	int		i[2];

	i[0] = 0;
	while (command[i[0]] != '\0')
	{
		if (command[i[0]] == '$')
		{
			i[1] = i[0] + 1;
			while (command[i[1]] != ' ' && command[i[1]] != D_QUOTE
				&& command[i[1]] != S_QUOTE && (command[i[1]]))
				i[1]++;
			command = swap_var(command, i);
		}
		i[0]++;
	}
	return (command);
}

static t_quotes_m	*add_quote_list(t_quotes_m *space, t_quotes_m	*new_quote)
{
	t_quotes_m	*tmp;

	new_quote = ft_calloc(1, sizeof(t_quotes_m));
	tmp = space;
	while (tmp->next_quote != NULL)
		tmp = tmp->next_quote;
	tmp->next_quote = new_quote;
	return (new_quote);
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
	//ft_printf("command = |%s|\n", command);
	return (command);
}

static char	*check_space(char *command, int idx, char q_id, t_quotes_m *space)
{
	t_quotes_m	*new_quote;
	int			space_count;
	int			string_count;
	int			i;
	int			j;

	i = 0;
	space_count = 0;
	string_count = 0;
	while (command[i] != '\0' && i < idx)
	{
		if (command[i] == ' ')
			string_count++;
		i++;
	}
	i++;
	j = i;
	while (command[i] != q_id)
	{
		if (command[i] == ' ')
			space_count++;
		i++;
	}
	if (space_count > 0)
	{
		new_quote = NULL;
		new_quote = add_quote_list(space, new_quote);
		new_quote->id_size = space_count - 1;
		new_quote->id = ft_calloc(space_count, sizeof(int));
		new_quote->split_c = string_count;
		i = 0;
		while (command[j] != q_id)
		{
			if (command[j] == ' ')
			{
				command[j] = '@';
				if (string_count == 0)
					new_quote->id[i] = j - 1;
				else
					new_quote->id[i] = j - idx - 1;
				//printf("new_quote->id[i]= %d, j = %d, idx = %d\n", new_quote->id[i], j, idx);
				i++;
			}
			j++;
		}
	}
	command = subs_quote(command, idx, q_id);
	return (command);
}

static char	*substitute_quotes(char *command, t_quotes_m *quote_space)
{
	int			simple_quote;
	int			double_quote;
	int			i;
	int			simple_i;
	int			double_i;

	simple_quote = 0;
	double_quote = 0;
	i = 0;
	while (command[i])
	{
		if (command[i] == S_QUOTE)
		{
			if (simple_quote == 0)
				simple_i = i;
			simple_quote++;
			if (simple_quote == 2)
			{
				command = check_space(command, simple_i, S_QUOTE, quote_space);
				i = 0;
				double_quote = 0;
				simple_quote = 0;
			}
		}
		else if (command[i] == D_QUOTE)
		{
			if (double_quote == 0)
				double_i = i;
			double_quote++;
			if (double_quote == 2)
			{
				command = check_space(command, double_i, D_QUOTE, quote_space);
				i = 0;
				simple_quote = 0;
				double_quote = 0;
			}
		}
		i++;
	}
	return (command);
}

static char	**swap_spaces(char **splitted,
		t_quotes_m *lst, t_quotes_m *tmp)
{
	while (lst->next_quote != NULL)
	{
		while (lst->id_size >= 0)
		{
			splitted[lst->split_c][lst->id[lst->id_size]] = ' ';
			lst->id_size--;
		}
		free(lst->id);
		tmp = lst->next_quote;
		free(lst);
		lst = tmp;
	}
	while (lst->id_size >= 0)
	{
		//printf("splitted=|%s|, i = %d, char = %c\n", splitted[lst->split_c], lst->id[lst->id_size], splitted[lst->split_c][lst->id[lst->id_size]]);
		splitted[lst->split_c][lst->id[lst->id_size]] = ' ';
		lst->id_size--;
	}
	free(lst->id);
	free(lst);
	return (splitted);
}

static char	**bring_spaces_back(char **splitted, t_quotes_m *lst)
{
	t_quotes_m		*tmp;

	tmp = NULL;
	if (lst->next_quote != NULL)
		tmp = lst->next_quote;
	free(lst);
	lst = tmp;
	if (lst == NULL)
		return (splitted);
	return (swap_spaces(splitted, lst, tmp));
}

char	**treat_quotes(char *command)
{
	t_quotes_m	*quote_space;
	char		**splitted;

	command = ft_strdup(command);
	command = expand_var(command);
	quote_space = ft_calloc(1, sizeof(t_quotes_m));
	command = substitute_quotes(command, quote_space);
	splitted = ft_split(command, ' ');
	splitted = bring_spaces_back(splitted, quote_space);
	free(command);
	return (splitted);
}
