/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_env_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-figu <mde-figu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 22:20:39 by nbarreir          #+#    #+#             */
/*   Updated: 2021/11/08 23:53:10 by mde-figu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (pwd != NULL)
	{
		ft_printf("%s\n", pwd);
		free(pwd);
		errno = 0;
	}
}

static void	print_echo(char **cmd, int i)
{
	while (cmd && cmd[i])
	{
		ft_printf("%s", cmd[i]);
		i++;
		if (cmd[i] != NULL)
			ft_printf(" ");
	}
}

int	echo(char **cmd)
{
	int		has_n;
	int		i;
	int		ret;

	has_n = 0;
	i = 1;
	if (cmd[i] != NULL)
	{
		ret = ft_strcmp(cmd[i], "-n");
		while (ret == FALSE)
		{
			has_n = 1;
			i++;
			if (cmd[i] == NULL)
				break ;
			ret = ft_strcmp(cmd[i], "-n");
		}
	}
	print_echo(cmd, i);
	if (has_n == FALSE)
		ft_printf("\n");
	errno = 0;
	return (1);
}

void	env(void)
{
	int	c;

	c = 0;
	while (g_shell.env->item[c] && c <= g_shell.env->size - 1)
	{
		ft_printf("%s=%s\n", g_shell.env->item[c]->key,
			g_shell.env->item[c]->value);
		c++;
	}
	errno = 0;
}

void	exit_terminal(char **cmd, char	**n_env)
{
	int	i;

	i = 0;
	if (cmd[1])
	{
		while (ft_isdigit(cmd[1][i]))
			i++;
		if (cmd[1][i] == '\0' && !cmd[2])
			errno = ft_atoi(cmd[1]);
		else if (cmd[2])
			errno = EPERM;
		else if (!cmd[2] && cmd[1][i] != '\0')
			errno = ENOENT;
	}
	else
		errno = 0;
	ft_free_split(cmd);
	ft_free_split(n_env);
	free_n_exit();
}
