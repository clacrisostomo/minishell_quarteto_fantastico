/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 19:05:55 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/07 19:05:57 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Deals with padding for pointers
*/

static void	print_pointer_a(t_flags *flags, int size)
{
	if (flags->width > size && flags->dash == 1)
	{
		flags->padding = ' ';
		flags->width = flags->width - size;
		print_padding(flags, flags->width);
	}
	reset_flags(flags);
}

void	print_pointer(t_flags *flags, char *ptr, int size)
{
	if (flags->width <= 0)
		flags->width = size;
	else if (flags->width > size && flags->dash == 0)
	{
		flags->width = flags->width - size;
		print_padding(flags, flags->width);
	}
	ft_putstr_f(flags, "0x", 2);
	if (flags->dot == 1 && flags->precision > size
		&& flags->width > flags->precision)
	{
		flags->width = flags->width - flags->precision;
		print_padding(flags, flags->width);
	}
	if (flags->dot == 1 && flags->precision > size
		&& flags->width < flags->precision)
	{
		flags->padding = '0';
		print_padding(flags, flags->precision - size + 2);
	}
	ft_putstr_f(flags, ptr, size - 2);
	print_pointer_a(flags, size);
}

/*
** Prints pointers
*/

void	print_p(t_flags *flags, unsigned long pointer)
{
	int				size;
	char			*ptr;

	flags->count++;
	ptr = hextoa(flags, pointer);
	size = (int)ft_strlen_f(ptr) + 2;
	if ((pointer == 0) && flags->dot == 1)
		size = 2;
	print_pointer(flags, ptr, size);
	free(ptr);
}
