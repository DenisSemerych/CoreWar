/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 16:08:09 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/10/28 12:37:26 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_count_words(const char *str, char c, int *ind)
{
	char	*tmp;
	int		count;
	int		chk;

	count = 0;
	*ind = 0;
	tmp = (char *)str;
	chk = 0;
	while (*tmp)
	{
		chk = 0;
		while (*tmp != c && *tmp)
		{
			chk = 1;
			tmp++;
		}
		if (chk == 1)
			count++;
		if (*tmp)
			tmp++;
	}
	return (count);
}

static	int	ft_count_letter(char *str, char c, int *stri)
{
	char	*tmp;
	int		count;

	if (!str)
		return ((int)NULL);
	tmp = str;
	count = 0;
	*stri = 0;
	while (*tmp != c && *tmp)
	{
		tmp++;
		count++;
	}
	return (count);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**arr;
	char	*stmp;
	int		ind;
	char	*tmp;
	int		stri;

	if (!s || !(arr = (char **)malloc(sizeof(char *)
					* ft_count_words(s, c, &ind) + 1)))
		return ((char **)NULL);
	stmp = (char *)s;
	while (*stmp)
	{
		if (*stmp != c && *stmp)
		{
			tmp = (char *)malloc(ft_count_letter(stmp, c, &stri) + 1);
			while (*stmp != c && *stmp)
				tmp[stri++] = *(stmp++);
			tmp[stri] = '\0';
			arr[ind++] = tmp;
		}
		if (*stmp)
			stmp++;
	}
	arr[ind] = 0;
	return (arr);
}
