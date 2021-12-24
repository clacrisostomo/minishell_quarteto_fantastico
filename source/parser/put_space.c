/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfico-vi <cfico-vi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 13:16:48 by cfico-vi          #+#    #+#             */
/*   Updated: 2021/12/24 16:56:16 by cfico-vi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*put_space_special_char(char *command, int *i, t_joker_m *joker_list)
{
	command = set_space_for_redir(command, i, joker_list);
	if (command == NULL)
	{
		free_joker_list(joker_list);
		free_n_exit();
	}
	return (command);
}
