/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 13:24:05 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/10/26 16:06:10 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*tmp;
	int		chk;

	if (!*needle)
		return ((char *)haystack);
	tmp = (char *)haystack;
	while (*tmp && len-- >= ft_strlen(needle))
	{
		chk = ft_memcmp(tmp, needle, ft_strlen(needle));
		if (chk == 0)
			return (tmp);
		tmp++;
	}
	return (NULL);
}
