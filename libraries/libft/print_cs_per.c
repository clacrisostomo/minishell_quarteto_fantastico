/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cs_per.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 19:05:43 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/07 19:05:44 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Prints %
*/

void	print_percent(t_flags *flags)
{
	int	size;

	size = 1;
	flags->count++;
	if (flags->width <= 0)
		flags->width = size;
	else if (flags->width > size && flags->dash == 0)
	{
		flags->width = flags->width - size;
		print_padding(flags, flags->width);
	}
	ft_putchar_f(flags, '%');
	if (flags->width > size && flags->dash == 1)
	{
		flags->width = flags->width - size;
		print_padding(flags, flags->width);
	}
	reset_flags(flags);
}

/*
** Prints chars
*/

void	print_c(t_flags *flags, int c)
{
	flags->count++;
	if (flags->asterisk == 1)
		flags->dash = 1;
	if (flags->width <= 0)
		flags->width = 1;
	else if (flags->width > 1 && flags->dash == 0)
	{
		flags->padding = ' ';
		print_padding(flags, flags->width - 1);
	}
	ft_putchar_f(flags, c);
	if (flags->width > 1 && flags->dash == 1)
		print_padding(flags, flags->width - 1);
	reset_flags(flags);
}

/*
** Prints strings
*/

void	print_s(t_flags *flags, char *s)
{
	int	size;

	if (!s)
		s = "(null)";
	size = (int)ft_strlen_f(s);
	flags->count++;
	if (flags->dot == 1 && flags->precision < size)
		size = flags->precision;
	if (flags->width <= 0)
		flags->width = size;
	else if (flags->width > size && flags->dash == 0)
	{
		if (flags->width > flags->precision && flags->zero == 0)
			flags->padding = ' ';
		flags->width = flags->width - size;
		print_padding(flags, flags->width);
	}
	ft_putstr_f(flags, s, size);
	if (flags->width > size && flags->dash == 1)
	{
		flags->width = flags->width - size;
		print_padding(flags, flags->width);
	}
	reset_flags(flags);
}
