/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfico-vi <cfico-vi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:11:32 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/13 17:34:44 by cfico-vi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtins(char **cmd)
{
	if (!(ft_strcmp(cmd[0], "echo")))
		return (TRUE);
	else if (!(ft_strcmp(cmd[0], "cd")))
		return (TRUE);
	else if (!(ft_strcmp(cmd[0], "pwd")))
		return (TRUE);
	else if (!(ft_strcmp(cmd[0], "env")))
		return (TRUE);
	else if (!(ft_strcmp(cmd[0], "export")))
		return (TRUE);
	else if (!(ft_strcmp(cmd[0], "unset")))
		return (TRUE);
	else if (!(ft_strcmp(cmd[0], "exit")))
		return (TRUE);
	else if (ft_isvar(cmd))
		return (TRUE);
	return (FALSE);
}

void	builtins(char **cmd, char **old_cmd, char **n_env)
{
	if (!(ft_strcmp(cmd[0], "echo")))
		echo(cmd);
	else if (!(ft_strcmp(cmd[0], "cd")))
		cd(cmd);
	else if (!(ft_strcmp(cmd[0], "pwd")))
		pwd();
	else if (!(ft_strcmp(cmd[0], "env")))
		env();
	else if (!(ft_strcmp(cmd[0], "export")))
		expt(cmd, 1);
	else if (!(ft_strcmp(cmd[0], "unset")))
		unset_(cmd);
	else if (!(ft_strcmp(cmd[0], "exit")))
		exit_terminal(cmd, n_env, old_cmd);
	else if (ft_isvar(cmd))
		expt(cmd, 0);
}

void	free_n_env(char **n_env)
{
	int	i;

	i = 0;
	if (n_env)
	{
		while (n_env[i])
		{
			free(n_env[i]);
			i++;
		}
		free(n_env);
	}
	return ;
}

void	ft_free_split(char **str)
{
	int	i;

	i = -1;
	if (!(str))
		return ;
	while (*(str + ++i) != NULL)
	{
		free(*(str + i));
		*(str + i) = NULL;
	}
	free(str);
	str = NULL;
}

void	execute(char **cmd, char **old_cmd)
{
	char	**n_env;

	if (cmd[0] != NULL)
	{
		n_env = array_to_str_arr(g_shell.env);
		if (is_builtins(cmd))
			builtins(cmd, old_cmd, n_env);
		else
		{
			if (ft_isdigit(ft_atoi(cmd[0])))
				ft_putendl_fd("Command not found", 2);
			else
				do_exec(cmd, n_env);
		}
		printf("oi execute\n");
		ft_free_split(n_env);
	}
}
