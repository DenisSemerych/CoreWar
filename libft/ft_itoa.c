/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 18:43:26 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/10/26 12:00:09 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	nb[12];
	int		c;
	int		sign;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	ft_bzero(nb, 12);
	c = 10;
	sign = 0;
	if (n < 0)
	{
		n *= -1;
		sign = 1;
	}
	while (n || c == 10)
	{
		nb[c] = n % 10 + '0';
		n /= 10;
		c--;
	}
	if (sign == 1)
		nb[c] = '-';
	else
		c++;
	return (ft_strdup(&nb[c]));
}