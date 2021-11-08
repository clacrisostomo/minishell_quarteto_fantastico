/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-figu <mde-figu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:47:33 by mde-figu          #+#    #+#             */
/*   Updated: 2021/06/16 13:49:08 by mde-figu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	i;
	int				calc;

	i = 0;
	while (i < n)
	{
		calc = ((*(unsigned char *)(s1 + i)) - (*(unsigned char *)(s2 + i)));
		if (calc != 0)
		{
			return (calc);
		}
		i++;
	}
	return (0);
}
