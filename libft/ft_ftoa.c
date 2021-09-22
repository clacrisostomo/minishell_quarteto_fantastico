/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-figu <mde-figu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 23:09:53 by mde-figu          #+#    #+#             */
/*   Updated: 2021/07/17 17:15:38 by mde-figu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*zero_exception(int int_part, char *int_str)
{
	char	*temp;

	if (int_part == 0)
	{
		temp = ft_strjoin("-", int_str);
		free(int_str);
		int_str = temp;
	}
	return (int_str);
}

static char	*after_point(int int_part, float float_part, int precision)
{
	char	*float_str;
	char	*entire_str;

	entire_str = ft_calloc(precision + 2, sizeof(char));
	*entire_str = '.';
	int_part = 0;
	float_part *= 10;
	while (float_part < 1 && int_part < precision)
	{
		int_part++;
		*(entire_str + int_part) = '0';
		float_part *= 10;
	}
	if (precision - int_part > 0)
	{
		float_part *= ft_pow_pos(10, precision - int_part - 1);
		float_part = (int)float_part;
		float_str = ft_itoa(float_part);
	}
	else
		float_str = ft_calloc(1, sizeof(char));
	ft_strlcpy(entire_str + int_part + 1, float_str, precision - int_part + 1);
	free(float_str);
	float_str = entire_str;
	return (float_str);
}

char	*ft_ftoa(float n, int precision)
{
	char	*int_str;
	char	*float_str;
	char	*entire_str;
	int		int_part;
	float	float_part;

	int_part = (int)n;
	int_str = ft_itoa(int_part);
	float_part = n - (float)int_part;
	if (float_part < 0)
	{
		float_part *= -1;
		int_str = zero_exception(int_part, int_str);
	}
	if (precision > 0)
	{
		float_str = after_point(int_part, float_part, precision);
		entire_str = ft_strjoin(int_str, float_str);
		free(int_str);
		free(float_str);
		return (entire_str);
	}
	return (int_str);
}
