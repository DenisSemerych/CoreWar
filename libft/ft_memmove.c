/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 15:39:07 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/10/25 13:43:38 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dp;
	unsigned char	*sp;

	dp = (unsigned char*)dst;
	sp = (unsigned char*)src;
	if (dp > sp && (size_t)(dp - sp) < len)
		while (len-- > 0)
			*(dp + len) = *(sp + len);
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
