/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-figu <mde-figu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 13:42:03 by mde-figu          #+#    #+#             */
/*   Updated: 2021/06/25 17:54:38 by mde-figu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*nstr;
	size_t	i;

	if (!s)
		return (NULL);
	if ((int)len <= 0 || (int)start < 0
		|| (int)start > (int)ft_strlen((char *)s) - 1)
	{
		return (ft_strdup(""));
	}
	nstr = (char *)ft_calloc(len + 1, sizeof(char));
	if (!nstr)
	{
		return (0);
	}
	i = 0;
	while (i < len && *(s + start) != '\0')
	{
		*(nstr + i) = *(s + start);
		i = i + 1;
		start = start + 1;
	}
	*(nstr + i) = '\0';
	return (nstr);
}
