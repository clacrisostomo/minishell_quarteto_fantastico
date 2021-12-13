/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_star.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 19:03:41 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/07 19:03:43 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_number(const char *str, t_flags *flags)
{
	flags->number = 0;
	if (!(ft_isdigit_f((int)str[flags->count])))
		return (0);
	while (ft_isdigit_f((int)str[flags->count]))
	{
		flags->number = ((flags->number) * 10) + (int)str[flags->count] - '0';
		flags->count++;
	}
	return (1);
}

void	check_star(t_flags *flags, va_list args, int *star)
{
	*star = va_arg(args, int);
	if (*star < 0)
	{
		if (flags->dot == 0)
		{
			flags->asterisk = 1;
			flags->dash = 1;
			*star = *star * (-1);
			flags->padding = ' ';
		}
		else
			flags->dot = 0;
	}
	flags->count++;
}

void	print_padding(t_flags *flags, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		ft_putchar_f(flags, flags->padding);
		i++;
	}
}

void	reset_flags(t_flags *flags)
{
	flags->negative = 0;
	flags->width = 0;
	flags->precision = -1;
	flags->dash = 0;
	flags->dot = 0;
	flags->asterisk = 0;
}
