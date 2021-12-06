/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mister_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirkios <mirkios@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 13:25:20 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/05 23:42:53 by mirkios          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	mr_redirect_out(char *file, int flag)
{
	int	file_fd;

	file_fd = open(file, flag, 0777);
	if (file_fd == -1)
	{
		ft_putendl_fd("Error: bad file decriptor", 2);
	}
	else
	{
		dup2(file_fd, STDOUT);
		close(file_fd);
	}
}

static void	mr_redirect_in(char *file, int flag)
{
	int	file_fd;

	file_fd = open(file, flag);
	if (file_fd == -1)
	{
		ft_putendl_fd("Error: bad file decriptor", 2);
	}
	else
		dup2(file_fd, STDIN);
}

void	mister_redirect(char *redirect, char *file, int *save_fd)
{
	if (!(ft_strcmp(redirect, ">")))
		mr_redirect_out(file, O_WRONLY | O_CREAT | O_TRUNC);
	else if (!(ft_strcmp(redirect, ">>")))
		mr_redirect_out(file, O_WRONLY | O_CREAT | O_APPEND);
	else if (!(ft_strcmp(redirect, "<")))
		mr_redirect_in(file, O_RDONLY | O_CREAT);
	else if (!(ft_strcmp(redirect, "<<")))
		dr_here(file, save_fd);
}

int	is_redirect(char *cmd)
{
	if (!(ft_strcmp(cmd, ">")))
		return (TRUE);
	else if (!(ft_strcmp(cmd, ">>")))
		return (TRUE);
	else if (!(ft_strcmp(cmd, "<")))
		return (TRUE);
	else if (!(ft_strcmp(cmd, "<<")))
		return (TRUE);
	return (FALSE);
}
