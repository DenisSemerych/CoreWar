/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chars_and_strings.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:09:04 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/12/04 19:42:35 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

char	*ft_create_chr(t_format *format, va_list ap, size_t *stringlen)
{
	char	*new;
	int		c;

	if (format->specif == 1)
		return (ft_create_wcr(va_arg(ap, wchar_t), stringlen));
	c = (char)va_arg(ap, int);
	new = (char*)malloc(2);
	new[0] = c;
	new[1] = '\0';
	*stringlen = 1;
	return (new);
}

char	*ft_create_str(t_format *format, va_list ap, size_t *stringlen)
{
	char *str;

	str = va_arg(ap, char*);
	*stringlen = 0;
	if (!str)
		str = ft_strdup("(null)");
	else if (format->specif == 1)
		return (ft_create_wsr(format, (wchar_t*)str, stringlen));
	else
		str = ft_strdup(str);
	while (str[*stringlen] && !(*stringlen == format->precision &&
				format->point))
		*stringlen += 1;
	if (*stringlen == format->precision && format->point)
		str[*stringlen] = '\0';
	return (str);
}

char	*ft_create_wcr(unsigned long long value, size_t *strlen)
{
	char	str[5];
	int		n;

	n = 0;
	ft_bzero(str, 5);
	*strlen = 1;
	ft_set_unicode(value, str);
	while (str[n] == 0 && n < 3)
		n++;
	*strlen = 4 - n;
	if ((int)*strlen > MB_CUR_MAX)
		g_errornum = 1;
	return (ft_strdup(&str[n]));
}

char	*ft_create_wsr(t_format *format, wchar_t *p, size_t *strlen)
{
	char	*str;
	int		n;
	size_t	wlen;
	char	*wchr;
	char	*temp;

	*strlen = 0;
	wlen = 0;
	n = -1;
	str = ft_strdup("");
	while (p[++n] && !(format->point && *strlen + wlen > format->precision))
	{
		wchr = ft_create_wcr(p[n], &wlen);
		if (!(format->point && *strlen + wlen > format->precision))
		{
			temp = ft_strjoin(str, wchr);
			free(str);
			free(wchr);
			str = temp;
			*strlen += wlen;
		}
		else
			free(wchr);
	}
	return (str);
}

char	*ft_create_percent(t_format *format, va_list ap, size_t *stringlen)
{
	if (ap)
		*stringlen = 1;
	format->size = 6;
	return (ft_strdup("%"));
}
