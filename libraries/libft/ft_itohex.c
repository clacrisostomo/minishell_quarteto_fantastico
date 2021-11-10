/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itohex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-figu <mde-figu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 23:01:14 by mde-figu          #+#    #+#             */
/*   Updated: 2021/06/25 17:56:26 by mde-figu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	convert_hex(int i)
{
	if (i == 10)
		return ('a');
	if (i == 11)
		return ('b');
	if (i == 12)
		return ('c');
	if (i == 13)
		return ('d');
	if (i == 14)
		return ('e');
	if (i == 15)
		return ('f');
	return (i + 48);
}

static long long	negative_tratament(long long n, size_t uint_max)
{
	if (n < 0)
		n = uint_max + n + 1;
	return (n);
}

char	*ft_int_to_hex(long long n)
{
	char	*c;
	char	*str;
	char	*char_temp;
	size_t	uint_max;

	uint_max = 4294967295;
	c = ft_calloc(2, sizeof(char));
	str = ft_calloc(2, sizeof(char));
	if (n == 0)
	{
		*str = '0';
		free(c);
		return (str);
	}
	n = negative_tratament(n, uint_max);
	while (n > 0)
	{
		c[0] = convert_hex(n % 16);
		char_temp = str;
		str = ft_strjoin(c, str);
		free(char_temp);
		n = n / 16;
	}
	free(c);
	return (str);
}
