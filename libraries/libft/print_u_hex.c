/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 19:06:01 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/07 19:06:03 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Deals with precision for u and hexadecimals
*/

static void	precision_positive(t_flags *flags, char *number, int size)
{
	if (flags->dot == 1 && flags->precision > size)
	{
		flags->padding = '0';
		print_padding(flags, flags->precision - size);
	}
	if (flags->dot == 1 && flags->precision <= 0 && *number == '0')
	{
		if (flags->width > size && flags->dash == 1)
		{
			flags->padding = ' ';
			if (flags->precision > size)
				flags->width = flags->width - flags->precision;
			else
				flags->width = flags->width - size;
			print_padding(flags, flags->width);
		}
		reset_flags(flags);
	}
}

void	print_positive(t_flags *flags, char *number, int size)
{
	if (flags->width <= 0)
		flags->width = size;
	else if (flags->width > size && flags->dash == 0)
	{
		if (flags->precision > size)
			flags->width = flags->width - flags->precision;
		else
			flags->width = flags->width - size;
		print_padding(flags, flags->width);
	}
	precision_positive(flags, number, size);
	ft_putstr_f(flags, number, size);
	if (flags->width > size && flags->dash == 1)
	{
		flags->padding = ' ';
		if (flags->precision > size)
			flags->width = flags->width - flags->precision;
		else
			flags->width = flags->width - size;
		print_padding(flags, flags->width);
	}
	reset_flags(flags);
}

/*
** Prints hexadecimals x and X
*/

void	print_hex(t_flags *flags, unsigned int num)
{
	int				size;
	char			*number;

	flags->count++;
	if (flags->dot == 1)
	{
		flags->zero = 0;
		flags->padding = ' ';
	}
	number = hextoa(flags, (unsigned long long)num);
	size = (int)ft_strlen_f(number);
	if (num == 0 && flags->dot == 1)
		size = 0;
	print_positive(flags, number, size);
	free(number);
}

/*
** Prints unsigned int
*/

void	print_u(t_flags *flags, unsigned int num)
{
	int				size;
	char			*number;

	flags->count++;
	if (flags->dot == 1)
	{
		flags->zero = 0;
		flags->padding = ' ';
	}
	number = utoa(num);
	size = (int)ft_strlen_f(number);
	if (num == 0 && flags->dot == 1)
		size = 0;
	print_positive(flags, number, size);
	free(number);
}
