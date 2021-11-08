/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:20:42 by cfico-vi          #+#    #+#             */
/*   Updated: 2021/11/07 00:44:32 by nbarreir         ###   ########.fr       */
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

static t_joker_m	*add_joker_list(t_joker_m *space, t_joker_m *new_joker)
{
	t_joker_m	*tmp;

	new_joker = ft_calloc(1, sizeof(t_joker_m));
	if (new_joker == NULL)
	{
		perror("Error: ");
		return (NULL);
	}
	tmp = space;
	while (tmp->next_jok != NULL)
		tmp = tmp->next_jok;
	tmp->next_jok = new_joker;
	return (new_joker);
}

static void	put_jokers_c_ctrl(char *cmd, t_joker_m *new_joker, int *i, int q_id)
{
	i[0] = 0;
	i[4] = i[2] + 1;
	while (cmd[i[4]] != q_id)
	{
		if (cmd[i[4]] == ' ')
		{
			cmd[i[4]] = JOK_C;
			if (i[3] == 0)
				new_joker->id[i[0]] = i[4] - 1;
			else
				new_joker->id[i[0]] = i[4] - i[1] - 1;
			i[0]++;
		}
		i[4]++;
	}
}

void	put_jokers_c(char *command, t_joker_m *joker_list, int *i, int q_id)
{
	t_joker_m	*new_joker;

	new_joker = NULL;
	new_joker = add_joker_list(joker_list, new_joker);
	if (new_joker == NULL)
	{
		free_joker_list(joker_list);
		free_n_exit();
	}
	new_joker->id = ft_calloc(i[4], sizeof(int));
	if (new_joker->id == NULL)
	{
		perror("Error: ");
		free_joker_list(joker_list);
		free_n_exit();
	}
	new_joker->id_size = i[4] - 1;
	new_joker->split_c = i[3];
	put_jokers_c_ctrl(command, new_joker, i, q_id);
}

void	free_joker_list(t_joker_m *lst)
{
	t_joker_m	*tmp;

	tmp = NULL;
	if (lst->next_jok != NULL)
		tmp = lst->next_jok;
	free(lst);
	lst = tmp;
	if (lst == NULL)
		return ;
	while (lst->next_jok != NULL)
	{
		if (lst->id)
			free(lst->id);
		tmp = lst->next_jok;
		free(lst);
		lst = tmp;
	}
	if (lst->id)
		free(lst->id);
	free(lst);
	return ;
}
