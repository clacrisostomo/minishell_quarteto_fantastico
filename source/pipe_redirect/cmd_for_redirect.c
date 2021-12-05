/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_for_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 17:58:49 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/05 17:58:51 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**new_cmd_for_redirect(char **cmd, int i, int j)
{
	char	**sub_cmd;
	int		k;
	int		c;

	(void)i;
	k = 0;
	c = 0;
	sub_cmd = (char **)calloc((j - 1), sizeof(char *));
	while (k != j)
	{
		if (k != i && k != (i + 1))
		{
			sub_cmd[c] = ft_strdup(cmd[k]);
			c++;
		}
		k++;
	}
	sub_cmd[c] = NULL;
	return (sub_cmd);
}

char	**make_command_redirect(char **cmd, int i, int *save_fd)
{
	char	**new_cmd;
	char	**recursion;
	int		j;

	j = 0;
	if (cmd[0] != NULL)
	{
		while (cmd[j] != NULL)
			j++;
		while ((!is_redirect(cmd[i])) && (cmd[i + 1]))
			i++;
		if (is_redirect(cmd[i]))
		{
			mister_redirect(cmd[i], cmd[i + 1], save_fd);
			new_cmd = new_cmd_for_redirect(cmd, i, j);
			ft_free_split(cmd);
			recursion = make_command_redirect(new_cmd, 0, save_fd);
			return (recursion);
		}
	}
	return (cmd);
}
