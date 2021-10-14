/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-figu <mde-figu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 21:47:05 by csantos-          #+#    #+#             */
/*   Updated: 2021/10/13 23:01:22 by mde-figu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_f(t_flags *flags, char c)
{
	write(1, &c, 1);
	flags->len++;
}

size_t	ft_strlen_f(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	ft_putstr_f(t_flags *flags, char *s, size_t size)
{
	size_t	i;

	i = 0;
	if (!s)
		return ;
	while (i < size)
	{
		ft_putchar_f(flags, s[i]);
		i++;
	}
	return ;
}

char	*ft_strdup_f(const char *s1)
{
	char	*str;
	int		i;

	str = 0;
	i = 0;
	str = (char *)malloc(ft_strlen_f(s1) + 1);
	if (!str)
		return (0);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_isdigit_f(int c)
{
	return (c >= 48 && c <= 57);
}
