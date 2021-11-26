/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 13:26:21 by nbarreir          #+#    #+#             */
/*   Updated: 2021/11/26 13:36:22 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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