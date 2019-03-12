/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 13:09:13 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/10/29 17:40:52 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strcat(char *s1, const char *s2)
{
	char	*tmp;
	int		len;

	tmp = (char *)s2;
	len = ft_strlen(s1);
	while (*tmp)
	{
		ft_memset(s1 + len, *tmp, 1);
		tmp++;
		len++;
	}
	*(s1 + len) = '\0';
	return (s1);
}
