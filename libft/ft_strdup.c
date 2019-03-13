/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 17:12:23 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/10/24 17:22:49 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*new;
	size_t	len;

	len = ft_strlen(s1);
	if (!(new = (char*)malloc(len + 1)))
		return (NULL);
	new = (char*)ft_memcpy((void*)new, (void*)s1, len);
	new[len] = '\0';
	return (new);
}
