/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 17:05:24 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/10/24 20:38:40 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char	*tmpsrc;
	char	*tmpdst;

	tmpdst = dst;
	tmpsrc = (void *)src;
	while (n)
	{
		*tmpdst = *((unsigned char *)tmpsrc);
		if (*tmpsrc == (char)c)
		{
			tmpdst++;
			return (tmpdst);
		}
		tmpdst++;
		tmpsrc++;
		n--;
	}
	return (NULL);
}
