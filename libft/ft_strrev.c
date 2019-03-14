/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:12:13 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/03/13 16:09:34 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strrev(char *str)
{
	int		n;
	int		m;
	int		len;
	char	buf;

	if (str)
	{
		n = 0;
		len = ft_strlen(str) - 1;
		m = len;
		if (str)
			while (n < m)
			{
				buf = str[n];
				str[n] = str[m];
				str[m] = buf;
				m--;
				n++;
			}
	}
}
