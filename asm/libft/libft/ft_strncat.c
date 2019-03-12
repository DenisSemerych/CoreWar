/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 13:20:53 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/10/25 16:20:27 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*tmp;

	tmp = s1 + ft_strlen(s1);
	while (*s2 && n--)
		ft_memset(tmp++, *(s2++), 1);
	*tmp = '\0';
	return (s1);
}
