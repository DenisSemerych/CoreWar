/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:15:03 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/11/01 15:34:23 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char *tmp1;
	unsigned char *tmp2;

	tmp1 = (unsigned char *)s1;
	tmp2 = (unsigned char *)s2;
	if (!n)
		return (0);
	if (!*tmp1 || !*tmp2)
		return (*tmp1 - *tmp2);
	while (*tmp1 == *tmp2 && --n && *tmp1)
	{
		tmp1++;
		tmp2++;
	}
	return (*tmp1 - *tmp2);
}
