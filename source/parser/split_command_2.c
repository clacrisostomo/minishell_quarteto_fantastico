/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:45:45 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/07 18:45:47 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*expand_quote_var(char *command, int *idx, int q_id)
{
	int	i;

	i = *idx;
	while (command[++i] != q_id)
	{
		if (command[i] == '$' && command[i + 1] != S_QUOTE)
			command = expand_var(command, i--);
	}
	return (command);
}
