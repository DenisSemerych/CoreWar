/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 10:09:11 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/10/29 17:47:41 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	char	*tmp;
	char	*buff;
	int		chk;

	tmp = (char *)s;
	chk = 0;
	while (*tmp)
	{
		if (*tmp == (char)c)
		{
			chk++;
			buff = tmp;
		}
		tmp++;
	}
	if ((char)c == *tmp)
		return (tmp);
	if (chk)
		return (buff);
	return (NULL);
}
