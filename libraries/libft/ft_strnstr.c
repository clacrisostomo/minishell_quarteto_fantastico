/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 19:02:38 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/07 19:02:40 by nbarreir         ###   ########.fr       */
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
