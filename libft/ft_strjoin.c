/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:41:40 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/10/25 17:11:16 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*fresh;
	size_t	len;

	if (s1 && s2)
	{
		len = ft_strlen(s1) + ft_strlen(s2);
		if ((fresh = (char*)malloc(len + 1)))
		{
			len = ft_strlen(s1) + ft_strlen(s2);
			ft_bzero(fresh, len + 1);
			fresh = ft_strcat(fresh, s1);
			fresh = ft_strcat(fresh, s2);
			return (fresh);
		}
		else
			return (NULL);
	}
	else
		return (NULL);
}
