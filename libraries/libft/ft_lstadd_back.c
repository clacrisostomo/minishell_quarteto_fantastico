/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-figu <mde-figu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 23:03:21 by mde-figu          #+#    #+#             */
/*   Updated: 2021/03/18 23:03:34 by mde-figu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*copy;

	copy = *lst;
	if (!copy)
		*lst = new;
	else
	{
		while (copy->next)
			copy = copy->next;
		copy->next = new;
	}
}
