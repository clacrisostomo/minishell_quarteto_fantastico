/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-figu <mde-figu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 23:58:57 by mde-figu          #+#    #+#             */
/*   Updated: 2021/06/25 17:58:34 by mde-figu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		len1;
	int		len2;
	char	*jointstr;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	jointstr = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!(jointstr))
		return (NULL);
	i = 0;
	while (i < len1)
	{
		jointstr[i] = s1[i];
		i++;
	}
	while (i < len2 + len1)
	{
		jointstr[i] = s2[i - len1];
		i++;
	}
	jointstr[i] = '\0';
	return (jointstr);
}
