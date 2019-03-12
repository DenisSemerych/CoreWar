/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 13:39:04 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/11/05 21:10:03 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*tmp;

	if (!s1 || !s2)
		return ((char *)NULL);
	tmp = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!tmp)
		return ((char *)NULL);
	tmp = ft_strcpy(tmp, s1);
	tmp = ft_strcat(tmp, s2);
	tmp[ft_strlen(tmp)] = '\0';
	return (tmp);
}
