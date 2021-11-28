/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mister_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 13:25:20 by nbarreir          #+#    #+#             */
/*   Updated: 2021/11/28 02:10:03 by nbarreir         ###   ########.fr       */
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

void	mister_redirect(char *redirect, char *file)
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

char	**make_command_redirect(char **cmd, int i)
{
	char	**new_cmd;
	int		j;
	int h = 0;

	j = 0;
	while (cmd[j] != NULL)
		j++;
	while ((!is_redirect(cmd[i])) && (cmd[i + 1]))
		i++;
	ft_putstr_fd("i = ", 2);
	ft_putnbr_fd(i, 2);
	ft_putstr_fd("\nj = ", 2);
	ft_putnbr_fd(j, 2);
	ft_putstr_fd("\n", 2);
	if (is_redirect(cmd[i]))
	{
		mister_redirect(cmd[i], cmd[i + 1]);
		new_cmd = new_cmd_for_redirect(cmd, i, j);
		while (new_cmd[h] != NULL)
		{
			ft_putstr_fd(new_cmd[h++], 2);
			ft_putstr_fd(" ", 2);
		}
		ft_putstr_fd("|\n", 2);
		ft_free_split(cmd);
		make_command_redirect(new_cmd, 0);
	}
	while (cmd[h] != NULL)
	{
		ft_putstr_fd("oxe", 2);
		ft_putstr_fd(cmd[h++], 2);
		ft_putstr_fd(" ", 2);
	}
	ft_putstr_fd("|\n", 2);
	ft_putstr_fd("oxo", 2);
	return (cmd);
}
