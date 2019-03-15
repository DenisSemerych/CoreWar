/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 14:57:24 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/12/01 15:42:53 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

char	*ft_create_adr(t_format *format, va_list ap,
		size_t *stringlen)
{
	char *new;
	void *p;

	p = va_arg(ap, void*);
	format->sign = 5;
	*stringlen = 0;
	if (p == 0 && format->point && format->precision == 0)
		return (ft_strdup(""));
	new = printf_itoa_base((unsigned long)p, 16, format, stringlen);
	return (new);
}

char	*ft_create_dec(t_format *format, va_list ap, size_t *stringlen)
{
	char		*new;
	long long	value;

	value = va_arg(ap, long long);
	*stringlen = 0;
	value = ft_get_dec_value(format, value);
	if (format->negative)
		format->sign = 1;
	else if (format->plus)
		format->sign = 2;
	else if (format->space)
		format->sign = 4;
	if (value == 0 && format->point && format->precision == 0)
		return (ft_strdup(""));
	new = printf_itoa_base(value, 10, format, stringlen);
	return (new);
}

char	*ft_create_oct(t_format *format, va_list ap,
		size_t *stringlen)
{
	char				*new;
	unsigned long long	value;

	value = va_arg(ap, unsigned long long);
	*stringlen = 0;
	value = ft_get_unsign_value(format->specif, value);
	if (format->sharp)
		format->sign = 3;
	if (value == 0 && ((format->point && format->precision == 0) ||
				format->sharp == 1))
		return (ft_strdup(""));
	new = printf_itoa_base(value, 8, format, stringlen);
	if (format->sharp && format->point && format->precision > *stringlen)
		format->sign = 0;
	return (new);
}

char	*ft_create_uns(t_format *format, va_list ap,
		size_t *stringlen)
{
	char				*new;
	unsigned long long	value;

	value = va_arg(ap, unsigned long long);
	*stringlen = 0;
	if (value == 0 && format->point && format->precision == 0)
		return (ft_strdup(""));
	value = ft_get_unsign_value(format->specif, value);
	new = printf_itoa_base(value, 10, format, stringlen);
	return (new);
}

char	*ft_create_hex(t_format *format, va_list ap,
		size_t *stringlen)
{
	char				*new;
	unsigned long long	value;

	value = va_arg(ap, unsigned long long);
	*stringlen = 0;
	if (value == 0 && format->point && format->precision == 0)
		return (ft_strdup(""));
	value = ft_get_unsign_value(format->specif, value);
	if (format->sharp)
	{
		if (format->size == 13 && value != 0)
			format->sign = 6;
		else if (format->size == 12 && value != 0)
			format->sign = 5;
	}
	new = printf_itoa_base(value, 16, format, stringlen);
	return (new);
}
