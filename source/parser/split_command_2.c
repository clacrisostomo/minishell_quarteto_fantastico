/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfico-vi <cfico-vi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:20:42 by cfico-vi          #+#    #+#             */
/*   Updated: 2021/12/22 17:18:59 by cfico-vi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	put_jokers_fill_jkrlist(char *command, t_joker_m *joker_list, int *i, int q_id)
{
	t_joker_m	*new_joker;

	new_joker = NULL;
	new_joker = add_joker_list(joker_list, new_joker);
	if (new_joker == NULL)
	{
		free_joker_list(joker_list);
		free_n_exit();
	}
	new_joker->split_c = i[3];
	new_joker->id_size = i[4] - 1;
	if (i[4] > 0)
	{
		new_joker->id = ft_calloc(i[4], sizeof(int));
		if (new_joker->id == NULL)
		{
			perror("Error: ");
			free_joker_list(joker_list);
			free_n_exit();
		}
		put_jokers_c_ctrl(command, new_joker, i, q_id);
	}
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
	////printf("%c    %s\n", q_id, command);
	while (command[++i] != q_id)
	{
		//printf("i antes do expand var = %c\n", command[i]);
		if (command[i] == '$' && command[i + 1] != S_QUOTE && command[i + 1] != D_QUOTE) //ó
			command = expand_var(command, i--);
		//printf("i depois do expand var = %c\n", command[i]);
		//printf("loopando\n");
		//write(1,"oi\n",3);

	}
	//write(1,"isso\n",5);
	return (command);
}
