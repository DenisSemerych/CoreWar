/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_reading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 12:32:24 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/12/04 19:39:24 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

static int		ft_get_flags(char c, t_format *format)
{
	if (c > 48 || c < 32)
		return (0);
	if (c == '-')
		format->minus = 1;
	else if (c == '+')
		format->plus = 1;
	else if (c == ' ')
		format->space = 1;
	else if (c == '#')
		format->sharp = 1;
	else if (c == '0' && (!(format->zero)) && format->point == 0)
		format->zero = 1;
	else if (c == '$')
		format->dollar = 1;
	else if (c == '.')
		format->point = 1;
	else if (c == 39)
		format->apostrophe = 1;
	else
		return (0);
	return (1);
}

static int		ft_get_spec(char *str, t_format *format)
{
	int spec;

	spec = format->specif;
	if ((*str == 'l' && *(str + 1) == 'l') ||
		(*str == 'h' && *(str + 1) == 'h'))
	{
		format->specif = ((*str == 'l') ? 4 : 5);
		return (2);
	}
	else
	{
		format->specif = ft_char_pos(*str, "~l~h~~Lzjt");
		if (format->specif == 0)
		{
			format->specif = spec;
			return (0);
		}
		if (spec > format->specif && spec != 5)
			format->specif = spec;
	}
	return (1);
}

static int		ft_get_size(char c, t_format *format)
{
	char	*sizes;
	int		n;

	sizes = "~CSDOUcsdouixX%pfFbBnr";
	n = ft_char_pos(c, sizes);
	if (!n)
		return (0);
	if (n < 6)
	{
		format->specif = 1;
		n += 5;
	}
	format->size = n;
	return (1);
}

static int		ft_get_value(char *str, t_format *format, va_list ap)
{
	int counter;
	int value;

	counter = 0;
	value = ft_atoi(&str[counter]);
	while (str[counter] <= '9' && str[counter] >= '0')
		counter++;
	if (str[counter] == '*' && (counter += 1))
		value = va_arg(ap, int);
	if (format->point)
	{
		if (value < 0 && !(format->point = 0))
			value = 0;
		format->precision = value;
	}
	else
	{
		if (value < 0 && (format->minus = 1))
			value = -value;
		format->width = value;
	}
	if ((str[counter] <= '9' && str[counter] >= '0') || str[counter] == '*')
		return (counter + ft_get_value(&str[counter], format, ap));
	return (counter);
}

int				ft_get_format(char *str, t_format *format, va_list ap)
{
	int counter;
	int i;

	counter = 0;
	while (str[counter])
	{
		i = counter;
		while (ft_get_flags(str[counter], format))
			counter++;
		if (ft_isdigit(str[counter]) || str[counter] == '*')
			counter += ft_get_value(&str[counter], format, ap);
		counter += ft_get_spec(&str[counter], format);
		if (ft_get_size(str[counter], format))
			return (counter + 1);
		if (i == counter)
			return (counter);
	}
	return (counter);
}
