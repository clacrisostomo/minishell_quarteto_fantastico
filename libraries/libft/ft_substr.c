/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 19:03:13 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/07 19:03:15 by nbarreir         ###   ########.fr       */
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
