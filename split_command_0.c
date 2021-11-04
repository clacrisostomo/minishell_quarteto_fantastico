/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantos- <csantos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:20:42 by cfico-vi          #+#    #+#             */
/*   Updated: 2021/11/03 23:04:44 by csantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*expand_error(char *command, int i)
{
	char		*str_errno;
	char		*str_start;
	char		*str_end;
	char		*str_start_val;

	str_errno = ft_itoa(g_shell.status_error);
	str_start = ft_substr(command, 0, i);
	str_end = ft_substr(command, i + 2, ft_strlen(command) - (i + 2));
	free(command);
	str_start_val = ft_strjoin(str_start, str_errno);
	free(str_errno);
	free(str_start);
	command = ft_strjoin(str_start_val, str_end);
	free(str_end);
	free(str_start_val);
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
