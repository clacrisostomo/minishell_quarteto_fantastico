/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 19:02:43 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/07 19:02:45 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			len;

	len = ft_strlen(s);
	while (len >= 0)
	{
		if (*(s + len) == (char)c)
			return ((char *)s + len);
		len = len - 1;
	}
	return (NULL);
}
