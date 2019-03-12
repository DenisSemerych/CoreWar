/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 19:47:27 by dsemeryc          #+#    #+#             */
/*   Updated: 2019/01/13 18:27:39 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/printf.h"

int				make_number(char **format)
{
	int			a;
	char		*tmp;

	if ((a = ft_atoi(*format)) > 0)
	{
		tmp = ft_itoa(a);
		*(format) += ft_strlen(tmp);
		tmp ? free(tmp) : tmp;
	}
	return (a > 0 ? a : 0);
}

char			*get_info(char *format, int arr[])
{
	format++;
	set_to_zero(arr);
	while (IS_FLAG(*format))
	{
		*format == '-' ? (arr[0] = *format++) : arr[0];
		*format == '0' ? (arr[1] = *format++) : arr[1];
		*format == '+' ? (arr[2] = *format++) : arr[2];
		*format == ' ' ? (arr[3] = *format++) : arr[3];
		*format == '#' ? (arr[4] = *format++) : arr[4];
	}
	arr[5] = make_number(&format);
	*format == '.' ? (format++ && (arr[6] = make_number(&format)))
		: (arr[6] = -42);
	ft_isdigit(*format) ? format++ : format;
	arr[7] = 0;
	while (IS_TYPEFLAG(*format))
	{
		if ((*format == 'j' || *format == 'z') && format++)
			arr[7] = 216;
		else
			arr[7] += *format++;
	}
	return (format);
}

int				print_string(char *str, int *arr)
{
	int			percision;

	percision = arr[6];
	if (!str)
		str = ft_strdup("(null)");
	else
		str = ft_strdup(str);
	if (percision != -42 && percision < (int)ft_strlen(str))
		str = ft_strsub(str, 0, percision);
	return (formate(str, arr, 's', 0));
}

const char		*switch_format(const char *format,
		int *num_of_sym, int *arr, va_list p1)
{
	if (IS_INTCONVERT(*format))
		*num_of_sym += print_int(va_arg(p1, void *), *format++, arr, 0);
	else if (*format == 's' && format++)
		*num_of_sym += print_string(va_arg(p1, char *), arr);
	else if ((*format == 'F' || *format == 'f') && arr[7] == 'L')
		*num_of_sym += print_float(va_arg(p1, long double), arr, *format++);
	else if (*format == 'f' || *format == 'F')
		*num_of_sym += print_float(va_arg(p1, double), arr, *format++);
	else if (*format == 'p' && format++)
		*num_of_sym += print_pointer(va_arg(p1, void *), arr);
	else if (*format)
		*num_of_sym += print_char(*format++, arr);
	return (format);
}

int				ft_printf(const char *format, ...)
{
	va_list		p1;
	int			arr[8];
	int			num_of_sym;

	va_start(p1, format);
	num_of_sym = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format = get_info((char *)format, arr);
			format = switch_format(format, &num_of_sym, arr, p1);
		}
		else
		{
			ft_putchar(*format++);
			num_of_sym++;
		}
	}
	va_end(p1);
	return (num_of_sym);
}
