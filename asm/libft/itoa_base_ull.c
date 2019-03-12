/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base_ull.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 19:43:53 by dsemeryc          #+#    #+#             */
/*   Updated: 2019/01/13 18:28:26 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/printf.h"

char					*ibull(unsigned long long num,
		int base, int per)
{
	char				*literals;
	char				*str;
	int					size;
	unsigned long long	tmp;

	if (IS_ZERO_PER(num, per) && base != 0)
		return (ft_strnew(1));
	literals = "0123456789abcdef";
	tmp = num;
	size = 2;
	while (tmp /= base)
		size++;
	str = (char *)malloc(size);
	str[--size] = '\0';
	while (size)
	{
		str[--size] = literals[num % base];
		num /= base;
	}
	return (str);
}
