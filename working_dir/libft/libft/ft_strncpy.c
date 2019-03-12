/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 11:04:11 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/10/25 12:59:06 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncpy(char *dst, const char *src, size_t len)
{
	dst = ft_memcpy(dst, src, len);
	if (ft_strlen(src) < len)
		ft_bzero(dst + ft_strlen(src), len - ft_strlen(src));
	return (dst);
}
