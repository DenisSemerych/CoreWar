/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base_long.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 19:41:46 by dsemeryc          #+#    #+#             */
/*   Updated: 2019/01/13 18:27:55 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/printf.h"

char			*ibl(long long num, int base, int *sign, int per)
{
	char		*literals;
	char		*str;
	int			size;
	long long	tmp;

	if (IS_ZERO_PER(num, per))
		return (ft_strnew(1));
	num < 0 ? (*sign = 1) : num;
	literals = "0123456789abcdef";
	tmp = num;
	size = 2;
	while (tmp /= base)
		size++;
	str = (char *)malloc(size);
	str[--size] = '\0';
	while (size)
	{
		str[--size] = literals[(*sign == 1 ? -1 : 1) * (num % base)];
		num /= base;
	}
	return (str);
}
