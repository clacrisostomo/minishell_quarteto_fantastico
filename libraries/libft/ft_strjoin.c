/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 19:01:58 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/07 19:02:00 by nbarreir         ###   ########.fr       */
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
