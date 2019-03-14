/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 11:25:51 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/10/25 11:33:26 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t m;

	m = 0;
	while (m < n)
	{
		if (*((unsigned char*)s1 + m) != *((unsigned char*)s2 + m))
			return (*((unsigned char*)s1 + m) - *((unsigned char*)s2 + m));
		m++;
	}
	return (0);
}
