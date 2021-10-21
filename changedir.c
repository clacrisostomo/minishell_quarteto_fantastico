/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changedir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-figu <mde-figu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 22:17:46 by nbarreir          #+#    #+#             */
/*   Updated: 2021/10/20 23:30:13 by mde-figu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

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
		ft_printf("Minishell: cd's argument is wrong\n");
		g_shell.status_error = 1;
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
			if (old)
			{
				ft_printf("%s\n", old);
				chdir(old);
			}
			else
				write(1, "minishell: cd: OLDPWD not set\n", 30);
		}
		else if (ft_strncmp(cmd[1], "~-", 5) == 0)
		{
			old = search_hash_by_key("OLDPWD");
			chdir(old);
		}
		else if (ft_strncmp(cmd[1], "~", 4) == 0
			|| ft_strncmp(cmd[1], "--", 4) == 0)
			chdir(home);
		else if (ft_strncmp(cmd[1], "/", 4) == 0)
			chdir(slash);
		else if (ft_strncmp(cmd[1], "/bin", 4) == 0)
			chdir("/bin");
		else
			chdir(cmd[1]);
		modify_hash_by_key("OLDPWD", tmp);
	}
	free(tmp);
	return (0);
}
