/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_n_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 19:08:19 by mde-figu          #+#    #+#             */
/*   Updated: 2021/12/14 00:46:21 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_str(void)
{
	int	c;

	c = 0;
	while (g_shell.env->item[c] && c <= g_shell.env->size - 1)
	{
		if (!ft_strcmp(g_shell.env->item[c]->key, "PATH"))
			return (g_shell.env->item[c]->value);
		c++;
	}
	c = 0;
	while (g_shell.local->item[c] && c <= g_shell.local->size - 1)
	{
		if (!ft_strcmp(g_shell.local->item[c]->key, "PATH"))
			return (g_shell.local->item[c]->value);
		c++;
	}
	return ("");
}

char	**get_paths(void)
{
	char	*paths;
	char	**ret;

	paths = get_path_str();
	ret = ft_split(paths, ':');
	return (ret);
}

char	*do_prompt(void)
{
	char	cwd[2048];
	char	*prompt;

	getcwd(cwd, 2048);
	prompt = ft_strjoin(cwd, "$ ");
	if (prompt == NULL)
	{
		perror("Error: ");
		free_n_exit();
	}
	return (prompt);
}
