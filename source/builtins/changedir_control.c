/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changedir_control.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:07:08 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/10 04:34:22 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	control_cd_minus(char *tmp)
{
	char	*old;

	old = search_array_by_key("OLDPWD");
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

void	control_cd_minus_two(char **cmd, char *slash, char *home)
{
	if (ft_strncmp(cmd[1], "~-", 5) == 0)
		chdir(search_array_by_key("OLDPWD"));
	else if (ft_strncmp(cmd[1], "~", 4) == 0
		|| ft_strncmp(cmd[1], "--", 4) == 0)
		chdir(home);
	else if (ft_strncmp(cmd[1], "/", 4) == 0)
		chdir(slash);
	else
		chdir(cmd[1]);
}

void	cd_error_file(char **cmd)
{
	ft_putstr_fd("Minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(cmd[1], STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
}
