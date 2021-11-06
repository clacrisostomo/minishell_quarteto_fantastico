/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changedir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-figu <mde-figu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 22:17:46 by nbarreir          #+#    #+#             */
/*   Updated: 2021/11/06 00:18:48 by mde-figu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

static int	control_cd_minus(char *old, char *tmp)
{
	if (old)
	{
		ft_printf("%s\n", old);
		chdir(old);
		errno = 0;
		return (0);
	}
	else
	{
		ft_putstr_fd("Minishell: cd: OLDPWD not set\n", STDERR_FILENO);
		free(tmp);
		return (EPERM);
	}
}

static void	control_cd_minus_with_friends(char **cmd, char *slash, char *home)
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

static void	cd_error_file(char **cmd, char *tmp)
{
	ft_putstr_fd("Minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(cmd[1], STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	free(tmp);
	errno = 2;
}

int	cd(char **cmd)
{
	char	*old;
	char	*tmp;
	char	*home;
	char	*slash;
	int		i;

	i = 1;
	tmp = NULL;
	home = search_hash_by_key("HOME");
	slash = "/";
	while (cmd[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("Minishell: cd: too many arguments\n", STDERR_FILENO);
		errno = EPERM;
		return (1);
	}
	tmp = getcwd(tmp, 0);
	if (i == 1)
	{
		modify_hash_by_key("OLDPWD", tmp);
		chdir(home);
	}
	if (i == 2)
	{	
		if (ft_strncmp(cmd[1], "-", 4) == 0)
		{
			old = search_hash_by_key("OLDPWD");
			errno = control_cd_minus(old, tmp);
			if(errno == 1)
				return (errno);
		}
		else
			control_cd_minus_with_friends(cmd, slash, home);
		/* else if (ft_strncmp(cmd[1], "~-", 5) == 0)
			chdir(search_hash_by_key("OLDPWD"));
		else if (ft_strncmp(cmd[1], "~", 4) == 0
			|| ft_strncmp(cmd[1], "--", 4) == 0)
			chdir(home);
		else if (ft_strncmp(cmd[1], "/", 4) == 0)
			chdir(slash);
		else if (ft_strncmp(cmd[1], "/bin", 4) == 0)
			chdir("/bin");
		else
			chdir(cmd[1]); */
		modify_hash_by_key("OLDPWD", tmp);
		if (errno == ENOENT)
		{
			cd_error_file(cmd, tmp);
			/* ft_putstr_fd("Minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd[1], STDERR_FILENO);
			ft_putstr_fd("cd: No such file or directory", STDERR_FILENO);
			free(tmp); */
			return (1);
		}
	}
	errno = 0;
	free(tmp);
	return (0);
}