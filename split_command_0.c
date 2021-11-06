/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfico-vi <cfico-vi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:20:42 by cfico-vi          #+#    #+#             */
/*   Updated: 2021/11/06 13:14:54 by cfico-vi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*expand_error(char *command, int i)
{
	char 	**str_var;
	int		j;

	str_var = (char **)ft_calloc(6, sizeof(char *));
	if (str_var == NULL)
	{
		perror("Error: ");
		free(command);
		return (NULL);
	}
	j = 0;
	while (j < 6)
		str_var[j++] = NULL;
	str_var[0] = command;
	str_var[1] = ft_substr(str_var[0], 0, i);
	if (str_var[1] == NULL)
	{
		perror("Error: ");
		ft_free_split(str_var);
		return (NULL);
	}
	str_var[2] = ft_itoa(errno);
	if (str_var[2] == NULL)
	{
		perror("Error: ");
		ft_free_split(str_var);
		return (NULL);
	}
	str_var[3] = ft_strjoin(str_var[1], str_var[2]);
	if (str_var[3] == NULL)
	{
		perror("Error: ");
		ft_free_split(str_var);
		return (NULL);
	}
	str_var[4] = ft_substr(str_var[0], i + 2, ft_strlen(str_var[0]) - (i + 2));
	if (str_var[4] == NULL)
	{
		perror("Error: ");
		ft_free_split(str_var);
		return (NULL);
	}
	command = ft_strjoin(str_var[3], str_var[4]);
	if (command == NULL)
	{
		perror("Error: ");
		ft_free_split(str_var);
		return (NULL);
	}
	ft_free_split(str_var);
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
	if (splitted == NULL)
	{
		perror("Error: ");
		free(command);
		free_joker_list(joker_list);
		free_n_exit();
	}
	free(command);
	splitted = unchange_jok_c(splitted, joker_list);
	return (splitted);
}
