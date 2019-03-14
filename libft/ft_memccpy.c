/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:31:09 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/10/27 16:07:18 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*p;
	size_t			m;
	unsigned char	sc;

	m = 0;
	if (n == 0)
		return (NULL);
	p = (unsigned char*)src;
	sc = (unsigned char)c;
	while (p[m] != sc && m < n)
		m++;
	if (m < n && p[m] == sc)
	{
		n = m + 1;
		dst = ft_memcpy(dst, src, n);
		return (((unsigned char*)dst + n));
	}
	ft_memcpy(dst, src, n);
	return (NULL);
}
