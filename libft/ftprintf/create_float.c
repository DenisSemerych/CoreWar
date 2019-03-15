/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 17:45:13 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/12/04 20:05:41 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

static long double		ft_get_double(t_format *format, va_list ap)
{
	long double value;

	if (format->specif == 6)
		value = va_arg(ap, long double);
	else
		value = va_arg(ap, double);
	if (value < 0)
	{
		format->sign = 1;
		value *= -1;
	}
	return (value);
}

static long double		ft_mult_dec_power(long double value, int power)
{
	while (power)
	{
		value *= 10;
		power--;
	}
	return (value);
}

static char				*printf_ftoa_base(__uint128_t value, int base,
		t_format *format, size_t *stringlen)
{
	char	num[70];
	char	*chars;
	int		len;

	ft_bzero(num, 70);
	*stringlen = 1;
	if (value == 0)
		return (ft_strdup("0"));
	if (format->size == 13)
		chars = "0123456789ABCDEF";
	else
		chars = "0123456789abcdef";
	len = 68;
	num[69] = '\0';
	while (value)
	{
		num[len] = chars[value % base];
		len--;
		value /= base;
	}
	*stringlen = 68 - len;
	return (ft_strdup(&num[len + 1]));
}

static char				*ft_check_double(t_format *format, long double value,
		size_t *stringlen)
{
	char *str;

	str = NULL;
	if (value != value)
		str = ft_strdup((format->size == 17) ? "NAN" : "nan");
	if (value == 1.0 / 0.0)
	{
		str = ft_strdup((format->size == 17) ? "INF" : "inf");
		if (format->plus)
			format->sign = 2;
	}
	if (str)
		*stringlen = ft_strlen(str);
	return (str);
}

char					*ft_create_float(t_format *format,
		va_list ap, size_t *stringlen)
{
	__uint128_t			precision;
	char				*number1;
	char				*number2;
	long double			d;
	long double			n;

	d = ft_get_double(format, ap);
	if ((number1 = ft_check_double(format, d, stringlen)))
		return (number1);
	precision = (format->point) ? (format->precision) : 6;
	n = ft_mult_dec_power(1, precision);
	d += 0.5 / n;
	number1 = printf_ftoa_base((__uint128_t)d, 10, format, stringlen);
	if (precision == 0)
		return (number1);
	d = d - (__uint128_t)d;
	if (d > 1)
		return (number1);
	d *= ft_mult_dec_power(1, precision);
	number1 = ft_strjoin_free(number1, ft_strdup("."));
	number2 = printf_ftoa_base((__uint128_t)d, 10, format, stringlen);
	number2 = ft_join_spec('0', precision - ft_strlen(number2), number2);
	number1 = ft_strjoin_free(number1, number2);
	*stringlen = ft_strlen(number1);
	return (number1);
}
