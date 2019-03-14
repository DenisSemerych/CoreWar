/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoabase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 18:03:32 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/10/29 17:05:15 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int value, int base)
{
	int len;

	len = 0;
	if (value == 0)
		return (1);
	if (value < 0)
		value *= -1;
	while (value > 0)
	{
		value /= base;
		len++;
	}
	return (len);
}

char		*ft_itoa_base(int value, int base)
{
	char	*num;
	char	*chars;
	int		m;
	int		len;
	long	numb;

	numb = (long int)value;
	chars = "0123456789abcdef";
	m = 0;
	len = ft_numlen(value, base);
	if (value < 0 && base == 10)
		m++;
	len += m;
	num = (char*)malloc(len + 1);
	if (m)
		num[0] = '-';
	if (value < 0)
		numb *= -1;
	num[len] = '\0';
	while (len > m)
	{
		num[--len] = chars[numb % base];
		numb /= base;
	}
	return (num);
}
