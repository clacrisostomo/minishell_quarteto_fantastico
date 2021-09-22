/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-figu <mde-figu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 17:22:53 by mde-figu          #+#    #+#             */
/*   Updated: 2021/09/17 13:55:04 by mde-figu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_len(const char *s, char c)
{
	int	i;

	i = 0;
	while (*s != '\0')
	{
		if (*s != c && (s[1] == c || s[1] == '\0'))
			i++;
		s++;
	}
	return (i);
}

static int	letter_len(const char *s, char c)
{
	int	i;

	i = 0;
	while (*s != c && *s != '\0')
	{
		i++;
		s++;
	}
	return (i);
}

static int	**freeentry(char **str, size_t i)
{
	size_t	j;

	j = 0;
	while (j <= i)
		free(str[j++]);
	free(str);
	return (0);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**str;
	size_t	i;
	size_t	ii;

	str = (char **)malloc(word_len(s, c));
	if (!s || !str)
		return ((char **)freeentry(str, sizeof(str)));
	i = 0;
	while (*s != '\0')
	{
		if (*s != '\0')
		{
			str[i] = (char *)malloc(letter_len(s, c));
			if (!str[i])
				return ((char **)freeentry(str, sizeof(str)));
			ii = 0;
			while (*s != c && *s != '\0')
				str[i][ii++] = *s++;
			str[i++][ii] = '\0';
		}
		if (*s)
			s++;
	}
	str[i] = 0;
	return (str);
}
