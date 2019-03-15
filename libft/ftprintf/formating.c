/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formating.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 15:18:37 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/12/04 19:40:41 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

char	*ft_join_spec(char c, size_t len, char *str)
{
	char *ch;
	char *new;

	if (len <= 0)
		return (str);
	ch = "0000000000000000000000000000000000000000";
	if (c == ' ')
		ch = "                                        ";
	while (len)
	{
		if (len <= 40)
		{
			new = ft_strjoin(&ch[40 - len], str);
			free(str);
			return (new);
		}
		new = ft_strjoin(ch, str);
		free(str);
		str = new;
		len -= 40;
	}
	return (str);
}

char	*ft_str_add_sign(int sn, char *str, size_t *strlen)
{
	char *sign;

	if (sn == 1)
		sign = "-";
	else if (sn == 2)
		sign = "+";
	else if (sn == 3)
		sign = "0";
	else if (sn == 4)
		sign = " ";
	else if (sn == 5)
		sign = "0x";
	else if (sn == 6)
		sign = "0X";
	else
		return (str);
	*strlen += ft_strlen(sign);
	sign = ft_strjoin(sign, str);
	free(str);
	return (sign);
}

char	*ft_str_add_pre_width(t_format *format, size_t *len, char *str)
{
	int n;
	int m;

	m = 0;
	if (len && format->size > 7 && *len < format->precision)
		m = format->precision - *len;
	n = format->width - m - *len;
	if (n < 0)
		n = 0;
	if (n && !(format->zero && format->precision > *len) && !(format->minus))
	{
		*len += n;
		return (ft_join_spec(' ', n, str));
	}
	else
		return (str);
}

char	*ft_add_post_width(t_format *format, char *str, size_t *stringlen)
{
	int		n;
	char	*temp;
	char	*temp2;

	if (format->minus != 1 && format->zero)
		return (str);
	n = format->width - *stringlen;
	if (n < 0)
		return (str);
	*stringlen += n;
	temp = ft_strdup("");
	temp = ft_join_spec(' ', n, temp);
	if ((format->size == 6) && *str == 0)
	{
		*str = ' ';
		temp2 = ft_strjoin(str, temp);
		*temp2 = 0;
		free(str);
		free(temp);
		return (temp2);
	}
	temp2 = ft_strjoin(str, temp);
	free(str);
	free(temp);
	return (temp2);
}

char	*ft_str_add_zero(t_format *format, size_t *len, char *str)
{
	int precision;
	int width;
	int n;
	int signlen;

	if (format->point && format->size > 7 && format->size != 16 &&
			format->size != 17)
		format->zero = 0;
	signlen = 0;
	n = 0;
	precision = format->precision - *len;
	if (precision > 0 && format->size > 7 && format->size != 14)
		n = precision;
	if (n && format->sign == 3)
		format->sign = 0;
	if (format->sign > 4)
		signlen = 2;
	else if (format->sign > 0)
		signlen = 1;
	width = format->width - n - *len - signlen;
	if (width > 0 && !(format->minus) && format->zero)
		n += width;
	*len += n;
	return (ft_join_spec('0', n, str));
}
