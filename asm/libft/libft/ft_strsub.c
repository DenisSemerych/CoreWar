/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 13:23:48 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/12/06 13:56:43 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*tmp;

	if (!s)
		return ((char *)NULL);
	tmp = ft_strnew(len);
	if (!tmp)
		return ((char *)NULL);
	tmp = ft_strncpy(tmp, &s[start], len);
	tmp[len] = '\0';
	return (tmp);
}
