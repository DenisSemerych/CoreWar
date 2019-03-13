/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 14:48:17 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/10/24 15:08:01 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int n;
	int m;
	int length;

	n = 0;
	if (needle[0] == '\0')
		return ((char*)haystack);
	length = ft_strlen(haystack) - ft_strlen(needle) + 1;
	if (length < 0)
		return (NULL);
	while (n < length)
	{
		if (haystack[n] == needle[0])
		{
			m = 0;
			while (needle[m] == haystack[n + m] && needle[m] != '\0')
				m++;
			if (needle[m] == '\0')
				return ((char*)&haystack[n]);
		}
		n++;
	}
	return (NULL);
}
