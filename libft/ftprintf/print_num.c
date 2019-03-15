/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 14:53:53 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/12/01 17:46:29 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

long long			ft_get_dec_value(t_format *format, unsigned long long num)
{
	long long	value;

	if (format->specif == 1)
		value = (long long)(long)num;
	else if (format->specif == 3)
		value = (long long)(short)num;
	else if (format->specif == 4)
		value = (long long)num;
	else if (format->specif == 5)
		value = (long long)(char)(int)num;
	else if (format->specif == 7)
		value = (long long)(size_t)num;
	else if (format->specif == 8)
		value = (long long)(intmax_t)num;
	else if (format->specif == 9)
		value = (long long)(ptrdiff_t)num;
	else
		value = (int)num;
	if (value < 0)
	{
		format->negative = 1;
		value *= -1;
	}
	return (value);
}

unsigned long long	ft_get_unsign_value(int specif, unsigned long long num)
{
	unsigned long long	value;

	if (specif == 0)
		value = (unsigned long long)(unsigned)num;
	else if (specif == 1)
		value = (unsigned long long)(unsigned long)num;
	else if (specif == 3)
		value = (unsigned long long)(unsigned short)num;
	else if (specif == 4)
		value = num;
	else if (specif == 5)
		value = (unsigned long long)(unsigned char)num;
	else if (specif == 7)
		value = (unsigned long long)(size_t)num;
	else if (specif == 8)
		value = (unsigned long long)(intmax_t)num;
	else if (specif == 9)
		value = (long long)(ptrdiff_t)num;
	else
		value = (unsigned long long)(unsigned)num;
	return (value);
}

static int			ft_get_apostrophe(t_format *format)
{
	if (format->apostrophe && (format->size == 8 || format->size == 10 ||
		format->size == 11))
		return (1);
	return (0);
}

char				*printf_itoa_base(unsigned long long value, int base,
		t_format *format, size_t *stringlen)
{
	char	num[70];
	char	*chars;
	int		len;
	int		leng;
	int		apostrophe;

	ft_bzero(num, 70);
	*stringlen = 1;
	if (value == 0)
		return (ft_strdup("0"));
	chars = (format->size == 13) ? "0123456789ABCDEF" : "0123456789abcdef";
	len = 69;
	leng = len;
	num[len] = '\0';
	apostrophe = ft_get_apostrophe(format);
	while (value && len-- && leng--)
	{
		if (apostrophe && len != 68 && (68 - leng) % 3 == 0)
			num[len--] = ',';
		num[len] = chars[value % base];
		value /= base;
	}
	*stringlen = 69 - len;
	return (ft_strdup(&num[len]));
}

char				*ft_create_bin(t_format *format, va_list ap,
		size_t *stringlen)
{
	char				*new;
	unsigned long long	value;

	value = va_arg(ap, unsigned long long);
	*stringlen = 0;
	if (value == 0 && format->point && format->precision == 0)
		return (0);
	new = printf_itoa_base(value, 2, format, stringlen);
	return (new);
}
