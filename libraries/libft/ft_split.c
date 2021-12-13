/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 19:01:27 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/07 19:01:29 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	wordlength(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i = i + 1;
	return (i);
}

static size_t	wordcounter(char const *s, char c)
{
	int		total;
	int		i;

	i = 0;
	total = 0;
	while (s[i] && s[i] == c)
		i = i + 1;
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i = i + 1;
		total = total + 1;
		while (s[i] && s[i] == c)
			i = i + 1;
	}
	return (total);
}

static char	*nextword(char const *s, char c)
{
	while (*s && *s == c)
		s = s + 1;
	return ((char *)s);
}

char	**ft_split(char const *s, char c)
{
	char	**retstr;
	size_t	i;
	size_t	words;

	if (s != NULL)
	{
		words = wordcounter(s, c);
		retstr = (char **)malloc(sizeof(char *) * (words + 1));
		if (!(retstr))
			return (NULL);
		i = 0;
		while (i < words)
		{
			s = nextword(s, c);
			retstr[i] = ft_substr(s, 0, wordlength(s, c));
			if (!retstr[i])
				return (NULL);
			i = i + 1;
			s += wordlength(s, c);
		}
		retstr[words] = NULL;
		return (retstr);
	}
	return (NULL);
}
