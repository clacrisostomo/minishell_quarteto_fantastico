/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miss_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 13:25:17 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/10 18:18:14 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	miss_pipe(char **cmd, int i, int *old_fd, int has_pipe)
{
	int	fd[2];

	if (*old_fd > 0)
	{
		dup2(*old_fd, STDIN);
		close(*old_fd);
	}
	if (!(ft_strcmp(cmd[i], "|")))
	{
		has_pipe = 1;
		pipe(fd);
		dup2(fd[1], STDOUT);
		close(fd[1]);
		*old_fd = dup(fd[0]);
		close(fd[0]);
	}
	return (has_pipe);
}

char	**cmd_till_pipe(char **cmd, int begin, int end)
{
	char	**sub_cmd;
	int		k;

	k = 0;
	sub_cmd = (char **)calloc((end - begin + 1), sizeof(char *));
	while (begin != end)
		sub_cmd[k++] = ft_strdup(cmd[begin++]);
	sub_cmd[k] = NULL;
	return (sub_cmd);
}
