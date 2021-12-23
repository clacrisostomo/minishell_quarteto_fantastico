/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_space_for_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfico-vi <cfico-vi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 21:52:11 by mirkios           #+#    #+#             */
/*   Updated: 2021/12/22 20:32:16 by cfico-vi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*put_space_before(char *cmd, int i)
{
	char	*ret;
	int		j;

	ret = ft_calloc(ft_strlen(cmd) + 1, sizeof(char *));
	if (ret == NULL)
	{
		perror("Error: ");
		free(cmd);
		return (NULL);
	}
	j = 0;
	while (j < i)
	{
		ret[j] = cmd[j];
		j++;
	}
	ret[j++] = ' ';
	while (cmd[i] != '\0')
		ret[j++] = cmd[i++];
	free(cmd);
	return (ret);
}

char	*put_space_after(char *cmd, int i)
{
	char	*ret;
	int		j;

	ret = ft_calloc(ft_strlen(cmd) + 1, sizeof(char *));
	if (ret == NULL)
	{
		perror("Error: ");
		free(cmd);
		return (NULL);
	}
	j = 0;
	while (j <= i)
	{
		ret[j] = cmd[j];
		j++;
	}
	ret[j++] = ' ';
	while (cmd[i] != '\0')
		ret[j++] = cmd[++i];
	free(cmd);
	return (ret);
}

int		count_tokens_till_idx(char *string, int idx)
{
	int		counter;
	int		i;

	i = 0;
	counter = 0;
	while (string[i] && i < idx)
	{
		if (string[i] == ' ')
			counter++;
	}
	return(counter);
}

int		check_joke_list(char *string, int j_idx, t_joker_m *tmp)
{
	int		string_counter;
	int		i;
	int		id_count;

	i = 0;
	string_counter = 0;
	while (string_counter < tmp->split_c && string[i] != '\0')
	{
		if (string[i] == ' ')
			string_counter++;
		i++;
	}
	id_count = 0;
	while(id_count <= tmp->id_size)
	{
		if(i + tmp->id[id_count] == j_idx)
			return (TRUE);
		id_count++;
	}
	return (FALSE);
}

int		check_jok_before_idx(char *string, int i, t_joker_m *list)
{
	int			is_jok;
	t_joker_m	*tmp;

	tmp = list->next_jok;
	if (string[i - 1] == JOK_C)
	{
		while (tmp->next_jok != NULL)
		{
			is_jok = check_joke_list(string, i - 1, tmp);
			if (is_jok == TRUE)
				return (TRUE);
			tmp = tmp->next_jok;
		}
		is_jok = check_joke_list(string, i - 1, tmp);
		if (is_jok == TRUE)
			return (TRUE);
	}
	return (FALSE);
}

char	*set_space_for_redir(char *cmd, int *i, t_joker_m *joker_list)
{
	int			j;
	int			is_jok;

	is_jok = check_jok_before_idx(cmd, *i, joker_list);
	if (*i != 0)
	{
		if (cmd[*i - 1] != ' ' && cmd[*i - 1] != PIPE && cmd[*i - 1] != INPUT
			&& cmd[*i - 1] != OUTPUT && !is_jok)
		{
			j = *i;
			cmd = put_space_before(cmd, j);
			if (cmd == NULL)
				return (NULL);
			(*i)++;
		}
	}
	if (cmd[*i] == cmd[*i + 1])
		(*i)++;
	if (cmd[*i + 1] != '\0' && cmd[*i + 1] != ' ')
	{
		j = *i;
		cmd = put_space_after(cmd, j);
		if (cmd == NULL)
			return (NULL);
	}
	return (cmd);
}
