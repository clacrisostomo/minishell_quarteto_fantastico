/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changedir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 22:17:46 by nbarreir          #+#    #+#             */
/*   Updated: 2021/11/07 03:15:07 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

static void	control_cd_minus(char *tmp)
{
	char	*old;

	old = search_hash_by_key("OLDPWD");
	if (old)
	{
		ft_printf("%s\n", old);
		chdir(old);
		errno = 0;
	}
	else
	{
		ft_putstr_fd("Minishell: cd: OLDPWD not set\n", STDERR_FILENO);
		free(tmp);
		errno = EPERM;
	}
}

static void	control_cd_minus_two(char **cmd, char *slash, char *home)
{
	if (ft_strncmp(cmd[1], "~-", 5) == 0)
		chdir(search_hash_by_key("OLDPWD"));
	else if (ft_strncmp(cmd[1], "~", 4) == 0
		|| ft_strncmp(cmd[1], "--", 4) == 0)
		chdir(home);
	else if (ft_strncmp(cmd[1], "/", 4) == 0)
		chdir(slash);
	else if (ft_strncmp(cmd[1], "/bin", 4) == 0)
		chdir("/bin");
	else
		chdir(cmd[1]);
}

static void	cd_error_file(char **cmd)
{
	ft_putstr_fd("Minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(cmd[1], STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
}

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
		modify_hash_by_key("OLDPWD", cd_list->tmp);
		chdir(cd_list->home);
	}
}

static void	cd_init(t_cd *cd_list, char **cmd)
{
	cd_list->i = cd_args(cmd, 1);
	cd_list->tmp = NULL;
	cd_list->home = search_hash_by_key("HOME");
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
		modify_hash_by_key("OLDPWD", cd_list.tmp);
		if (errno == ENOENT)
			cd_error_file(cmd);
	}
	free(cd_list.tmp);
	return (errno);
}
