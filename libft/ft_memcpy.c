/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 13:48:15 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/10/25 10:38:53 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*p;
	size_t			m;

	m = 0;
	p = (unsigned char*)dst;
	while (m < n)
	{
		*p = *((unsigned char*)src + m);
		p++;
		m++;
	}
	return (dst);
}
