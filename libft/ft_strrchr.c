/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 15:29:39 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/10/24 15:33:28 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	n;
	char	*answ;

	answ = NULL;
	n = 0;
	if (!s)
		return (NULL);
	while (s[n] != '\0')
	{
		if ((unsigned char)s[n] == (unsigned char)c)
			answ = (char*)&s[n];
		n++;
	}
	if ((unsigned char)s[n] == (unsigned char)c)
		answ = (char*)&s[n];
	return (answ);
}
