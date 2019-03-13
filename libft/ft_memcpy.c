/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 13:48:15 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/03/13 16:11:10 by dzaporoz         ###   ########.fr       */
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
