/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 17:31:11 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/10/25 11:35:09 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t flen;

	flen = ft_strlen(src);
	dst = ft_memcpy((void*)dst, (void*)src, len);
	if (flen < len)
		ft_memset(&dst[flen], '\0', len - flen);
	return (dst);
}
