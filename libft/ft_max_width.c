/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-figu <mde-figu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 23:06:49 by mde-figu          #+#    #+#             */
/*   Updated: 2021/03/18 23:07:01 by mde-figu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	maximum(int arg_size, ...)
{
	int		max;
	int		current;
	va_list	numbers;

	va_start(numbers, arg_size);
	max = va_arg(numbers, int);
	while (--arg_size > 0)
	{
		current = va_arg(numbers, int);
		if (current > max)
			max = current;
	}
	va_end(numbers);
	return (max);
}
