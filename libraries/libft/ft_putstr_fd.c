/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:59:39 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/07 18:59:40 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	counter;

	counter = 0;
	if (!str)
		return ;
	while (str[counter] != '\0')
	{
		write(fd, &str[counter], 1);
		counter++;
	}
}
