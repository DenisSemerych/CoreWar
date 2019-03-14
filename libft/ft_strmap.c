/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:15:01 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/10/25 14:50:55 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	unsigned int	n;
	char			*fresh;

	n = 0;
	if (!s || !f)
		return (NULL);
	else if ((fresh = (char*)malloc(ft_strlen(s) + 1)))
	{
		while (n < ft_strlen(s))
		{
			fresh[n] = f(s[n]);
			n++;
		}
		fresh[n] = '\0';
	}
	else
		return (NULL);
	return (fresh);
}
