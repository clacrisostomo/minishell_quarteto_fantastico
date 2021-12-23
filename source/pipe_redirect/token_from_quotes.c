/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_from_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfico-vi <cfico-vi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 11:16:34 by cfico-vi          #+#    #+#             */
/*   Updated: 2021/12/23 11:16:53 by cfico-vi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_token_from_quotes(char *special_char, char *token, int idx)
{
	if (!ft_strcmp(token, special_char))
	{
		if (!g_shell.esc_idx[idx])
			return (TRUE);
	}
	return (FALSE);
}
