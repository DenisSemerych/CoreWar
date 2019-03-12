/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_int128.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 19:39:29 by dsemeryc          #+#    #+#             */
/*   Updated: 2019/01/13 18:27:23 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/printf.h"

char		*ft_itoa_uint128(__uint128_t num)
{
	char		*str;
	int			size;
	__uint128_t	tmp;
	__uint128_t	base;

	tmp = num;
	base = 10;
	size = 2;
	while (tmp /= 10)
		size++;
	str = (char *)malloc(size);
	str[--size] = '\0';
	while (size)
	{
		str[--size] = num % base + '0';
		num /= base;
	}
	return (str);
}
