/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:58:53 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/07 18:58:54 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	set_flags(t_flags *flags)
{
	flags->type = 0;
	flags->zero = 0;
	flags->dash = 0;
	flags->padding = ' ';
	flags->width = 0;
	flags->precision = -1;
	flags->number = 0;
	flags->count = 0;
	flags->len = 0;
	flags->dot = 0;
	flags->negative = 0;
	flags->asterisk = 0;
}

int	ft_printf(const char *input, ...)
{
	const char	*str;
	t_flags		flags;
	va_list		args;

	va_start(args, input);
	set_flags(&flags);
	str = ft_strdup_f(input);
	if (!str)
		return (0);
	while (str[flags.count])
	{
		if (str[flags.count] == '%')
		{
			flags.count++;
			get_flags(str, &flags, args);
		}
		else
		{
			ft_putchar_f(&flags, str[flags.count]);
			flags.count++;
		}
	}
	free((char *)str);
	va_end(args);
	return (flags.len);
}
