/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 18:06:48 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/10/24 21:41:54 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	char *tmpdst;
	char *tmpsrc;

	tmpdst = dst;
	tmpsrc = (void *)src;
	if (tmpdst >= tmpsrc)
	{
		tmpdst += len;
		tmpsrc += len;
		while (len)
		{
			*--tmpdst = *--tmpsrc;
			len--;
		}
	}
	else
	{
		while (len)
		{
			*tmpdst++ = *tmpsrc++;
			len--;
		}
	}
	return (dst);
}
