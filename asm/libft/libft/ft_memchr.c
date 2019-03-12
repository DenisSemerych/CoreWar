/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 21:45:36 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/10/29 17:39:20 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memchr(const void *s, int c, size_t n)
{
	char	*tmp;

	tmp = (void *)s;
	while (n)
	{
		if (*tmp == (char)c)
			return (tmp);
		tmp++;
		n--;
	}
	return (NULL);
}
