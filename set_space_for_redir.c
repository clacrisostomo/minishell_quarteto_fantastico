/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_space_for_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirkios <mirkios@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 21:52:11 by mirkios           #+#    #+#             */
/*   Updated: 2021/10/30 00:04:59 by mirkios          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*put_space_before(char *cmd, int i)
{
	char	*ret;
	int		j;

	ret = ft_calloc(ft_strlen(cmd) + 1, sizeof(char *));
	j = 0;
	while (j < i)
	{
		ret[j] = cmd[j];
		j++;
	}
	ret[j++] = ' ';
	while (cmd[i] != '\0')
		ret[j++] = cmd[i++];
	free(cmd);
	//cmd = ret;
	//free(ret);
	return (ret);
}

char	*put_space_after(char *cmd, int i)
{
	char	*ret;
	int		j;

	ret = ft_calloc(ft_strlen(cmd) + 1, sizeof(char *));
	j = 0;
	while (j <= i)
	{
		ret[j] = cmd[j];
		j++;
	}
	ret[j++] = ' ';
	while (cmd[i] != '\0')
		ret[j++] = cmd[++i];
	free(cmd);
	//cmd = ret;
	//free(ret);
	return (ret);
}


char	*set_space_for_redir(char *cmd, int *i)
{
    int j;
    
	ft_printf("chegando: %s\n", cmd);
	if (*i != 0)
	{
		if (cmd[*i - 1] != ' ')
        {
            j = *i;
			cmd = put_space_before(cmd, j);
			(*i)++;
        }
	}
	ft_printf("pós put space before: %s\n", cmd); 
	if (cmd[*i] == cmd[*i + 1])
		(*i)++;
	if (cmd[*i + 1] != '\0' && cmd[*i + 1] != ' ')
    {
			
        j = *i;
		cmd = put_space_after(cmd, j);	
    }
	ft_printf("pós put space after: %s\n", cmd);
	return (cmd);
}