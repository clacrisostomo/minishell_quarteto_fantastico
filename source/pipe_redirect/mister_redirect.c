/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mister_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 13:25:20 by nbarreir          #+#    #+#             */
/*   Updated: 2021/11/26 20:18:56 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void mr_redirect_out(char *file, int flag)
{
	int file_fd;

	file_fd = open(file, flag, 0777); //open(file.txt, all_flags, premission for file)
	if (file_fd == -1)
	{
		printf("ERROR REDIRECT\n");
	}
	else
	{
		dup2(file_fd, STDOUT);
		close(file_fd);
	}
}

static void mr_redirect_in(char *file, int flag)
{
	int file_fd;

	file_fd = open(file, flag); //open(file.txt, all_flags, premission for file)
	if (file_fd == -1)
	{
		printf("ERROR REDIRECT\n");
	}
	else
	{
		dup2(file_fd, STDIN);
		close(file_fd);
	}
}

void	mister_redirect(char *redirect, char* file)
{
	if (!(ft_strcmp(redirect, ">")))
		mr_redirect_out(file, O_WRONLY | O_CREAT | O_TRUNC);
	else if (!(ft_strcmp(redirect, ">>")))
		mr_redirect_out(file, O_WRONLY | O_CREAT | O_APPEND);
	else if (!(ft_strcmp(redirect, "<")))
		mr_redirect_in(file, O_RDONLY | O_CREAT);
	//else if (!(ft_strcmp(cmd, "<<")))
}

int	is_redirect(char *cmd)
{
	if (!(ft_strcmp(cmd, ">")))
		return (1);
	else if (!(ft_strcmp(cmd, ">>")))
		return (1);
	else if (!(ft_strcmp(cmd, "<")))
		return (1);
	else if (!(ft_strcmp(cmd, "<<")))
		return (1);
	return (0);
}

char **make_command_redirect(char **cmd, int i)
{
	while (is_redirect(cmd[i]) == 0 && (cmd[i + 1]))
		i++;
	if(is_redirect(cmd[i]))
	{
		printf("%s\n", cmd[i]);
		//mister_redirect()
		return(cmd);
	}
	else
		return (cmd);
}