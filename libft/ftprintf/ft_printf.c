/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 14:50:35 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/12/04 19:41:31 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

char		*ft_create_string(t_format *format, va_list ap,
		size_t *stringlen)
{
	static char *(*ft_ptr_arr[22])(t_format *format, va_list ap, size_t*);

	if (!ft_ptr_arr[6])
	{
		ft_ptr_arr[6] = ft_create_chr;
		ft_ptr_arr[7] = ft_create_str;
		ft_ptr_arr[8] = ft_create_dec;
		ft_ptr_arr[9] = ft_create_oct;
		ft_ptr_arr[10] = ft_create_uns;
		ft_ptr_arr[11] = ft_create_dec;
		ft_ptr_arr[12] = ft_create_hex;
		ft_ptr_arr[13] = ft_create_hex;
		ft_ptr_arr[14] = ft_create_percent;
		ft_ptr_arr[15] = ft_create_adr;
		ft_ptr_arr[16] = ft_create_float;
		ft_ptr_arr[17] = ft_create_float;
		ft_ptr_arr[18] = ft_create_bin;
		ft_ptr_arr[19] = ft_create_bin;
		ft_ptr_arr[21] = ft_create_err;
	}
	if (format->size > 5 && format->size < 20)
		return (ft_ptr_arr[format->size](format, ap, stringlen));
	return (ft_strdup(""));
}

char		*ft_put_string(t_format *format, size_t *offset, va_list ap,
		char *str)
{
	size_t				stringlen;
	char				*new;

	if (str == NULL)
		return (ft_strdup(""));
	if (format->size == 0)
	{
		if (!(*str))
			return (ft_strdup(""));
		new = (char*)malloc(2);
		new[0] = *str;
		new[1] = '\0';
		stringlen = 1;
	}
	else
		new = ft_create_string(format, ap, &stringlen);
	new = ft_str_add_zero(format, &stringlen, new);
	if (format->sign)
		new = ft_str_add_sign(format->sign, new, &stringlen);
	if (format->minus == 0)
		new = ft_str_add_pre_width(format, &stringlen, new);
	new = ft_add_post_width(format, new, &stringlen);
	*offset += stringlen;
	return (new);
}

char		*ft_subprintf(char *str, size_t *chars, size_t *offset, va_list ap)
{
	t_format		flags;
	size_t			counter;
	char			*new;
	int				*n;

	ft_bzero(&flags, sizeof(flags));
	counter = ft_get_format(++str, &flags, ap);
	if (flags.size == 20)
	{
		*offset = counter + 1;
		n = va_arg(ap, int*);
		*n = *chars;
		return (ft_strdup(""));
	}
	new = ft_put_string(&flags, chars, ap, &str[counter]);
	if (flags.size == 0 && str[counter])
		counter++;
	*offset = counter + 1;
	return (new);
}

char		*ft_simple_print(char *str, size_t *chars, size_t *offset)
{
	int n;

	n = 0;
	while (str[n] != '%' && str[n] != '\0')
		n++;
	*chars += n;
	*offset = n;
	return (ft_strsub(str, 0, n));
}

int			ft_printf(const char *format, ...)
{
	char			*new;
	size_t			chars;
	size_t			offset;
	size_t			lastchars;
	va_list			ap;

	g_errornum = 0;
	va_start(ap, format);
	chars = 0;
	offset = 0;
	lastchars = 0;
	new = ft_strdup("");
	while (*format && !g_errornum)
	{
		new = ft_strjoin_free_spec(new, (*format == '%') ? (ft_subprintf((char*)
						format, &chars, &offset, ap)) : (ft_simple_print((char*)
							format, &chars, &offset)), &lastchars, &chars);
		lastchars = chars;
		format += offset;
	}
	va_end(ap);
	if (!g_errornum)
		write(1, new, chars);
	free(new);
	return (g_errornum ? -1 : chars);
}
