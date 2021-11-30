/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mister_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirkios <mirkios@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 13:25:20 by nbarreir          #+#    #+#             */
/*   Updated: 2021/11/28 22:41:50 by mirkios          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	mr_redirect_out(char *file, int flag)
{
	int	file_fd;

	file_fd = open(file, flag, 0777);
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

static void	mr_redirect_in(char *file, int flag)
{
	int	file_fd;

	file_fd = open(file, flag);
	if (file_fd == -1)
	{
		printf("ERROR REDIRECT\n");
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

char	**new_cmd_for_redirect(char **cmd, int i, int j)
{
	char	**sub_cmd;
	int		k;
	int		c;

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
	return (cmd);
}
