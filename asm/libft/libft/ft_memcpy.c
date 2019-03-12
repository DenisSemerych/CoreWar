/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:24:15 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/10/24 18:04:18 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char *tmpdst;
	char *tmpsrc;

	tmpdst = dst;
	tmpsrc = (void *)src;
	while (n)
	{
		*tmpdst++ = *tmpsrc++;
		n--;
	}
	return (dst);
}
