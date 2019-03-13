/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 17:31:11 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/10/27 13:49:54 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *fresh;

	if (s && (fresh = (char*)malloc(len + 1)))
	{
		fresh = ft_memcpy((void*)fresh, (void*)(s + start), len);
		fresh[len] = '\0';
		return (fresh);
	}
	else
		return (NULL);
}
