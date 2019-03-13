/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 16:17:43 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/10/27 14:58:03 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(char *str, char c)
{
	int words;

	words = 0;
	while (*str == c)
		str++;
	while (*str)
	{
		if (*str == c && *(str - 1) != c)
			words++;
		str++;
	}
	if (*(str - 1) != c)
		words++;
	return (words);
}

char		**ft_strsplit(char const *s, char c)
{
	char	*p;
	char	*z;
	char	**tab;
	int		n;

	if (!s)
		return (NULL);
	p = (char*)s;
	n = 0;
	if (!(tab = (char**)malloc((ft_countwords(p, c) + 1) * sizeof(char *))))
		return (NULL);
	while (*p == c)
		p++;
	while (*p)
	{
		z = p;
		while (*p != c && *p != '\0')
			p++;
		tab[n++] = ft_strsub(z, 0, p - z);
		while (*p == c && *p)
			p++;
	}
	tab[n] = NULL;
	return (tab);
}
