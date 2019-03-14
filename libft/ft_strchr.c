/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 15:20:54 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/03/14 13:21:40 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int n;

	n = 0;
	while (s[n] != '\0')
	{
		if ((unsigned char)s[n] == (unsigned char)c)
			return ((char*)&s[n]);
		n++;
	}
	if ((unsigned char)s[n] == (unsigned char)c)
		return ((char*)&s[n]);
	return (NULL);
}
