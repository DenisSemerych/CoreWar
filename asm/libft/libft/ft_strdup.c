/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 09:42:18 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/11/01 15:35:16 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strdup(const char *str)
{
	char			*dup;
	int				len;

	len = ft_strlen(str) + 1;
	dup = (char *)malloc(len);
	if (dup == NULL)
		return (NULL);
	else
		dup = (char *)ft_memcpy(dup, str, len);
	return (dup);
}
