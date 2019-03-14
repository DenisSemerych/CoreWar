/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 15:09:26 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/10/27 16:19:28 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t n;
	size_t m;

	n = 0;
	if (needle[0] == '\0')
		return ((char*)haystack);
	while (n < len && haystack[n] != '\0')
	{
		if (haystack[n] == needle[0])
		{
			m = 0;
			while (needle[m] == haystack[n + m] && needle[m] != '\0' &&
					(n + m) <= len)
				m++;
			if (needle[m] == '\0')
				return ((char*)&haystack[n]);
		}
		n++;
	}
	return (NULL);
}
