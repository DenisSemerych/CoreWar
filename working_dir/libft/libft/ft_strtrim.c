/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 14:07:10 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/10/29 17:47:57 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_if_had_letter(const char *s)
{
	char	*tmp;

	tmp = (char *)s;
	while (*tmp == ' ' || *tmp == '\n' || *tmp == '	')
		tmp++;
	if (!*tmp)
		return (0);
	return (1);
}

static	int	ft_getsize(const char *s)
{
	int		size;
	char	*tmp;

	size = 0;
	tmp = (char *)s;
	while (*tmp == ' ' || *tmp == '\n' || *tmp == '	')
		tmp++;
	while (*tmp && ft_if_had_letter(tmp))
	{
		tmp++;
		size++;
	}
	return (size);
}

char		*ft_strtrim(char const *s)
{
	char	*tmp;
	char	*stmp;
	size_t	wrote;

	if (!s)
		return ((char *)NULL);
	stmp = (char *)s;
	tmp = (char *)malloc(ft_getsize(s) + 1);
	if (!tmp)
		return ((char *)NULL);
	while (*stmp == ' ' || *stmp == '\t' || *stmp == '\n')
		stmp++;
	wrote = 0;
	while (*stmp && ft_if_had_letter(stmp))
	{
		tmp[wrote] = *stmp;
		stmp++;
		wrote++;
	}
	tmp[wrote] = '\0';
	return (tmp);
}
