/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 10:47:32 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/10/29 13:33:29 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strstr(const char *haystack, const char *needle)
{
	char	*tmp;
	int		chk;

	if (!*needle)
		return ((char *)haystack);
	tmp = (char *)haystack;
	while (*tmp)
	{
		chk = ft_memcmp(tmp, needle, ft_strlen(needle));
		if (chk == 0)
			return (tmp);
		tmp++;
	}
	return (NULL);
}
