/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-figu <mde-figu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:17:55 by mirkios           #+#    #+#             */
/*   Updated: 2021/06/25 17:55:38 by mde-figu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *small, size_t len)
{
	size_t	needle_len;

	needle_len = ft_strlen(small);
	if (!needle_len)
		return ((char *)big);
	while (*big && len >= needle_len)
	{
		if (!ft_strncmp(big, small, needle_len))
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}
