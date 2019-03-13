/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:19:27 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/10/25 14:51:56 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	n;
	char		*fresh;

	n = 0;
	if (!s || !f)
		return (NULL);
	else if ((fresh = (char*)malloc(ft_strlen(s) + 1)))
	{
		while (n < ft_strlen(s))
		{
			fresh[n] = f(n, s[n]);
			n++;
		}
		fresh[n] = '\0';
	}
	else
		return (NULL);
	return (fresh);
}
