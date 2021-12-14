/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miss_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 13:25:17 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/14 00:46:21 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	miss_pipe(char **cmd, int i, int *old_fd)
{
	int	fd[2];

	if (*old_fd > 0)
	{
		dup2(*old_fd, STDIN);
		close(*old_fd);
	}
	if (!(ft_strcmp(cmd[i], "|")))
	{
		pipe(fd);
		dup2(fd[1], STDOUT);
		close(fd[1]);
		*old_fd = dup(fd[0]);
		close(fd[0]);
	}
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
