/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 15:52:46 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/10/25 13:00:42 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	int m;
	int n;
	int max;

	m = ft_strlen(dst);
	n = 0;
	max = (int)dstsize;
	while (src[n] != '\0' && (m + n) < (max - 1))
	{
		dst[m + n] = src[n];
		n++;
	}
	if (n > 0)
		dst[m + n] = '\0';
	n = ft_strlen(src);
	if ((size_t)m > dstsize)
		m = dstsize;
	return (m + n);
}
