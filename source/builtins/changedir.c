/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changedir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 22:17:46 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/08 02:47:57 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	cd_args(char **cmd, int i)
{
	while (cmd[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("Minishell: cd: too many arguments\n", STDERR_FILENO);
		errno = EPERM;
	}
	return (i);
}

static void	cd_home(t_cd *cd_list)
{
	if (cd_list->i == 1)
	{
		insert_or_modify_by_key("OLDPWD", cd_list->tmp);
		chdir(cd_list->home);
	}
}

static void	cd_init(t_cd *cd_list, char **cmd)
{
	cd_list->i = cd_args(cmd, 1);
	cd_list->tmp = NULL;
	cd_list->home = search_array_by_key("HOME");
	cd_list->slash = "/";
	errno = 0;
}

int	cd(char **cmd)
{
	t_cd	cd_list;

	cd_init(&cd_list, cmd);
	if (errno == EPERM)
		return (errno);
	cd_list.tmp = getcwd(cd_list.tmp, 0);
	cd_home(&cd_list);
	if (cd_list.i == 2)
	{
		if (ft_strncmp(cmd[1], "-", 4) == 0)
		{
			control_cd_minus(cd_list.tmp);
			if (errno == EPERM)
				return (errno);
		}
		else
			control_cd_minus_two(cmd, cd_list.slash, cd_list.home);
		insert_or_modify_by_key("OLDPWD", cd_list.tmp);
		if (errno == ENOENT)
			cd_error_file(cmd);
	}
	free(cd_list.tmp);
	return (errno);
}
