/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfico-vi <cfico-vi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:20:42 by cfico-vi          #+#    #+#             */
/*   Updated: 2021/12/23 13:19:27 by cfico-vi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*treat_quotes_ctrl(char *cmd, int *i, int q_id, t_joker_m *j_list)
{
	put_jokers_fill_jkrlist(cmd, j_list, i, q_id);
	cmd = subs_quote(cmd, i[2], q_id);
	if (cmd == NULL)
	{
		free_joker_list(j_list);
		free_n_exit();
	}
	return (cmd);
}

static char	*treat_quotes(char *cmd, int *idx, int q_id, t_joker_m *j_list)
{
	int	i[5];

	i[0] = 0;
	i[4] = 0;
	i[3] = count_string(cmd, idx, i, q_id);
	i[2] = *idx;
	if (q_id == D_QUOTE)
	{
		cmd = expand_quote_var(cmd, idx, q_id);
		if (cmd == NULL)
		{
			free_joker_list(j_list);
			free_n_exit();
		}
	}
	while (cmd[++(*idx)] != q_id)
	{
		if (cmd[*idx] == ' ')
			i[4]++;
	}
	(*idx) = (*idx) - 3;
	cmd = treat_quotes_ctrl(cmd, i, q_id, j_list);
	return (cmd);
}

static char	*check_second_quote(char *command, int *idx,
				int q_id, t_joker_m *joker_list)
{
	int	j;

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

char	*treat_command_ctrl(char *cmd, t_joker_m *joker_list, int i)
{
	if (cmd[i + 1] == D_QUOTE || cmd[i + 1] == S_QUOTE)
		cmd[i] = ' ';
	else if (cmd[i + 1] == '?')
	{
		cmd = expand_error(cmd, i);
		if (cmd == NULL)
		{
			free_joker_list(joker_list);
			free_n_exit();
		}
	}
	else if (cmd[i + 1])
	{
		cmd = expand_var(cmd, i--);
		if (cmd == NULL)
		{
			free_joker_list(joker_list);
			free_n_exit();
		}
	}
	return (cmd);
}

char	*treat_command(char *command, t_joker_m *joker_list)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '$' && (command[i + 1] == ' '
				|| command[i + 1] == '\0'))
			break ;
		if (command[i] == '$')
			command = treat_command_ctrl(command, joker_list, i);
		else if (command[i] == D_QUOTE)
			command = check_second_quote(command, &i, D_QUOTE, joker_list);
		else if (command[i] == S_QUOTE)
			command = check_second_quote(command, &i, S_QUOTE, joker_list);
		else if (command[i] == INPUT || command[i] == PIPE
			|| command[i] == OUTPUT)
			command = put_space_special_char(command, &i, joker_list);
		i++;
	}
	return (command);
}
