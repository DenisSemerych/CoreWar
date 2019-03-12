/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 10:34:32 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/10/25 11:03:42 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strcpy(char *dst, const char *src)
{
	char	*tmpsrc;
	char	*tmpdst;

	tmpsrc = (char *)src;
	tmpdst = dst;
	while (*tmpsrc)
		*tmpdst++ = *tmpsrc++;
	*tmpdst = '\0';
	return (dst);
}
