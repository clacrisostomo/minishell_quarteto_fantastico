/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfico-vi <cfico-vi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:20:42 by cfico-vi          #+#    #+#             */
/*   Updated: 2021/12/22 21:12:44 by cfico-vi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int 	arr_arr_size(char **splitted)
{
	int		i;

	i = 0;
	while(splitted[i] != NULL)
		i++;
	return(i);
}

static void	position_escapes(t_joker_m *lst, char **split)
{
	t_joker_m	*tmp;
	int			arr_size;

	g_shell.esc_idx = (int *)ft_calloc(arr_arr_size(split) + 1, sizeof(int));
	tmp = lst;
	while (tmp->next_jok)
	{
		g_shell.esc_idx[tmp->split_c] = TRUE;
		tmp = tmp->next_jok;
	}
	g_shell.esc_idx[tmp->split_c] = TRUE;
}

static char	**unchange_jok_c(char **splitted, t_joker_m *lst)
{
	t_joker_m	*tmp;
	int			i;

	tmp = NULL;
	if (lst->next_jok != NULL)
		tmp = lst->next_jok;
	free(lst);
	lst = tmp;
	if (lst == NULL)
		return (splitted);
	else
	{
		position_escapes(lst, splitted);
		splitted = swap_spaces(splitted, lst, tmp);
	}
/* 	i = 0;
	while (i < g_shell.esc_s)
	{
		printf("splited{esc_idx} ~%s~\t idx ~%d~\n", splitted[g_shell.esc_idx[i]], g_shell.esc_idx[i]);
		i++;
	} */
 	printf("splited{esc_idx} ~%s~\t idx ~%d~\n", splitted[g_shell.esc_idx[i]], g_shell.esc_idx[i]);
	return (splitted);
}

static void	split_command_control(char **split, t_joker_m *j_list, char *cmd)
{
	if (split == NULL)
	{
		perror("Error: ");
		free(cmd);
		free_joker_list(j_list);
		free_n_exit();
	}
}

char	**split_command(char *command)
{
	t_joker_m	*joker_list;
	char		**splitted;

	command = ft_strdup(command);
	if (command == NULL)
	{
		perror("Error: ");
		free_n_exit();
	}
	joker_list = ft_calloc(1, sizeof(t_joker_m));
	if (joker_list == NULL)
	{
		perror("Error: ");
		free(command);
		free_n_exit();
	}
	command = treat_command(command, joker_list);
	splitted = ft_split(command, ' ');
	split_command_control(splitted, joker_list, command);
	free(command);
	splitted = unchange_jok_c(splitted, joker_list);
	return (splitted);
}
