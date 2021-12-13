/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:46:01 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/07 18:46:03 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	t_joker_m	*tmp;

	tmp = NULL;
	if (lst->next_jok != NULL)
		tmp = lst->next_jok;
	free(lst);
	lst = tmp;
	if (lst == NULL)
		return (splitted);
	return (swap_spaces(splitted, lst, tmp));
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
