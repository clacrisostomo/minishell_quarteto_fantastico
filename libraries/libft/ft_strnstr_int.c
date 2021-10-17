/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantos- <csantos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 00:04:32 by csantos-          #+#    #+#             */
/*   Updated: 2021/10/17 00:22:36 by csantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnstr_indie(const char *big, const char *small, size_t len)
{
	size_t	needle_len;
	char	*tmp;
	int		i;

	i = 0;
	tmp = (char *)big;
	needle_len = ft_strlen(small);
	if (!needle_len)
		return (0);
	while (*tmp && len >= needle_len)
	{
		if (ft_strncmp(tmp, small, needle_len) == 0)
			return (i + needle_len);
		tmp++;
		i++;
	}
	return (INT_MAX);
}
