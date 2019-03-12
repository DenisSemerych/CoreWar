/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 12:33:24 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/10/29 17:45:00 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char					*ft_strmapi(const char *s, char (*f)
						(unsigned int, char))
{
	char				*tmp;
	unsigned int		ind;

	if (!s)
		return ((char *)NULL);
	tmp = ft_strdup(s);
	if (!tmp)
		return ((char *)NULL);
	ind = 0;
	while (tmp[ind])
	{
		tmp[ind] = f(ind, tmp[ind]);
		ind++;
	}
	return (tmp);
}
