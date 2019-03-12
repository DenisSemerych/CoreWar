/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 21:45:11 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/11/01 19:43:44 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	char	*tmp;
	int		ind;

	ind = 0;
	if (!s || !f)
		return ((char *)NULL);
	tmp = ft_strdup(s);
	if (!tmp)
		return ((char *)NULL);
	while (tmp[ind])
	{
		tmp[ind] = f(tmp[ind]);
		ind++;
	}
	return (tmp);
}
