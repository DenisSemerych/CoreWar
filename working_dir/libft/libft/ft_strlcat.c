/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 16:26:24 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/11/01 16:53:24 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		ind;

	ind = 0;
	if (dstsize <= ft_strlen(dst))
		return (ft_strlen(src) + dstsize);
	while ((dst[ind] != '\0') && ind < (dstsize - 1))
		ind++;
	while (ind < (dstsize - 1) && *src)
		dst[ind++] = *src++;
	dst[ind] = '\0';
	return (ft_strlen(dst) + ft_strlen(src));
}
