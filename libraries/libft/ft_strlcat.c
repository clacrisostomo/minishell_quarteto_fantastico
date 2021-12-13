/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 19:02:03 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/07 19:02:05 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstlen)
{
	size_t	i;
	size_t	j;

	if (dstlen <= ft_strlen(dst))
		return (ft_strlen(src) + dstlen);
	i = 0;
	while (dst[i] != '\0')
	{
		i++;
	}
	j = 0;
	while (i + j < dstlen - 1 && src[j] != '\0')
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	while (src[j] != '\0')
		j++;
	return (i + j);
}
