/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 15:34:41 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/12/03 13:45:32 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

char	*ft_create_err(t_format *format, va_list ap, size_t *stringlen)
{
	long long int	ern;
	char			*new;

	ern = errno;
	if (ap)
		*stringlen = 0;
	if (format->negative)
		format->sign = 1;
	else if (format->plus)
		format->sign = 2;
	else if (format->space)
		format->sign = 4;
	new = printf_itoa_base(ern, 10, format, stringlen);
	return (new);
}

char	*ft_strjoin_free_spec(char *s1, char *s2, size_t *oldlen,
		size_t *newlen)
{
	char	*fresh;

	if (s1 && s2)
	{
		if ((fresh = (char*)malloc(*oldlen + *newlen + 1)))
		{
			ft_bzero(fresh, *oldlen + *newlen + 1);
			fresh = ft_memcpy(fresh, s1, *oldlen);
			ft_memcpy(&fresh[*oldlen], s2, *newlen);
			free(s1);
			free(s2);
			return (fresh);
		}
		else
			return (NULL);
	}
	else if (s1)
		return (ft_strdup(s1));
	else if (s2)
		return (ft_strdup(s2));
	else
		return (NULL);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*fresh;
	size_t	len;

	if (s1 && s2)
	{
		len = ft_strlen(s1) + ft_strlen(s2);
		if ((fresh = (char*)malloc(len + 1)))
		{
			len = ft_strlen(s1) + ft_strlen(s2);
			ft_bzero(fresh, len + 1);
			fresh = ft_strcat(fresh, s1);
			fresh = ft_strcat(fresh, s2);
			free(s1);
			free(s2);
			return (fresh);
		}
		else
			return (NULL);
	}
	else if (s1)
		return (ft_strdup(s1));
	else if (s2)
		return (ft_strdup(s2));
	else
		return (NULL);
}

size_t	ft_char_pos(char c, char *str)
{
	size_t n;

	n = 0;
	while (str[n])
	{
		if (c == str[n])
			return (n);
		n++;
	}
	return (0);
}

void	ft_set_unicode(unsigned int value, char *str)
{
	if (value < 177)
		str[3] = value;
	else
	{
		str[3] = (value & 63) | 128;
		if (value > 0176 && value < 03777)
		{
			str[2] = (value >> 6) | 192;
			return ;
		}
		else
			str[2] = ((value >> 6) & 63) | 128;
		if (value < 0177777)
		{
			str[1] = ((value >> 12) & 15) | 224;
			return ;
		}
		else
			str[1] = ((value >> 12) & 63) | 128;
		if (value > 65536)
			str[0] = ((value >> 18) & 7) | 240;
	}
}
