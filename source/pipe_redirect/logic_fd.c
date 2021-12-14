/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 13:26:21 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/14 00:46:21 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_origin_fd(int *save_fd)
{
	save_fd[0] = dup(0);
	save_fd[1] = dup(1);
}

void	reset_fd(int *save_fd)
{
	dup2(save_fd[0], 0);
	close(save_fd[0]);
	dup2(save_fd[1], 1);
	close(save_fd[1]);
}

int	is_file(char *file)
{
	int		i;

	i = 0;
	if (is_redirect(file))
		return (FALSE);
	while (file[i])
	{
		if (file[i] == '/' || file[i] == '(' || file[i] == ')'
			|| file[i] == '&' || file[i] == '|' || file[i] == '~'
			|| file[i] == '*')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	have_file_after_redirect(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (is_redirect(cmd[i]))
		{
			if (cmd[i + 1] != NULL)
			{
				if (!is_file(cmd[i + 1]))
					return (FALSE);
			}
			else if (cmd[i + 1] == NULL)
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
