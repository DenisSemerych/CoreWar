/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 13:33:01 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/03/14 14:21:16 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	uint64_t		*lp;
	uint64_t		*end;
	unsigned char	*ch;

	ch = (unsigned char*)b;
	end = (uint64_t*)(ch + len);
	if (len > sizeof(uint64_t))
		len %= sizeof(uint64_t);
	while (len != 0)
	{
		*ch++ = c;
		len--;
	}
	if (ch != (unsigned char*)end)
	{
		lp = (uint64_t*)ch;
		*lp = (unsigned char)c;
		*lp |= *lp << 8;
		*lp |= *lp << 16;
		*lp |= (*lp << 16) << 16;
		while (lp != end)
			*lp++ = ((uint64_t*)ch)[0];
	}
	return (b);
}
