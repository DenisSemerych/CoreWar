/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 21:56:49 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/10/29 14:33:01 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*tmps1;
	unsigned char	*tmps2;

	tmps1 = (unsigned char *)s1;
	tmps2 = (unsigned char *)s2;
	if (!n)
		return (0);
	while (n)
	{
		if (*tmps1 == *tmps2 && n != 1)
		{
			tmps1++;
			tmps2++;
		}
		n--;
	}
	return (*tmps1 - *tmps2);
}
