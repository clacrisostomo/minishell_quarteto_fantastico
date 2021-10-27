/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retoken_pipe_or_redir.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-figu <mde-figu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:44:58 by mde-figu          #+#    #+#             */
/*   Updated: 2021/10/27 00:56:40 by mde-figu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	retoken_catch_pipe(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while(cmd[i][j])
		{
			if (cmd[i][j] == '|')
				return (j);
			j++;
		}
		i++;
	}
	return (0);
}

int retoken_catch_redir_output(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while(cmd[i][j])
		{
			if (cmd[i][j] == '>')
				return (j);
			j++;
		}
		i++;
	}
	return (0);
}

int retoken_catch_redir_input(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while(cmd[i][j])
		{
			if (cmd[i][j] == '<')
				return (j);
			j++;
		}
		i++;
	}
	return (0);
}

int retoken_catch_redir_append_out(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while(cmd[i][j])
		{
			if (cmd[i][j] == '>' && cmd[i][j + 1] == '>')
				return (j); // << mudar esse retorno!!! precisa pegar J para comandos sem espacos
			j++;
		}
		i++;
	}
	return (0);
}

char	**insert_arr_to_arr(char **target, char **addition, int pos)
{
	int			i;
	int			j;
	int			c;
	int			z;
	char	**ret;
	char	**tmp;

	j = 0;
	i = 0;
	while(target[c])
		c++;
	while(addition[z])
		z++;
	ret = (char **)ft_calloc(z + c, sizeof(char *));
	ret = target;
	tmp = addition;
	while(z >= 0)
	{
		while(c >= 0 && c != pos)
		{
			ret[c + 1] = ret[c];split
		c++;
		z--;
	}
	while(tmp[z])
		z++;
	while(ret[i])
	{
		if (i == pos)
		{
			while(z >= 0)
			{
				ret[i] = tmp[j];
				j++;
				z--;
			}
		}
	i++;
	}
	free(tmp);
	return(ret);
}

char	**retoken_pipe_or_redir(char **cmd)
{
	char **tmp;
	char **splat;
	int		i;
	int		j;

	tmp = cmd;
	i = catch_pipe(tmp);
	j = retoken_catch_pipe(tmp);
	if (i != 0)
	{
		if (j != 0)
		{
			if (tmp[i][j + 1] != '\0' || tmp[i][0] != '|')
			{
				splat = ft_strcut(tmp[i], '|');
				tmp = insert_arr_to_arr(tmp, splat, i);
			}
		}
	}
	i = catch_redir_output(tmp);
	j = retoken_catch_redir_output(cmd);
	if (i != 0)
	{
		if (j != 0)
		{
			if (tmp[i][j + 1] != '\0' || tmp[i][0] != '>')
			{
				splat = ft_strsplit(tmp[i], '>');
				tmp = insert_arr_to_arr(tmp, splat, i);
			}
		}
	}
	return (tmp);
}
