/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 13:24:17 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/10/28 15:38:18 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n)
{
	char	*tmp;
	int		size;
	int		tmpn;
	int		sign;

	size = 2;
	sign = 0;
	tmpn = n;
	while (tmpn /= 10)
		size++;
	if (n < 0 && size++ && (sign = 1))
		n = -n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (!(tmp = (char *)malloc(size)))
		return ((char *)NULL);
	tmp[--size] = '\0';
	while ((n / 10) && (tmp[--size] = (n % 10) + 48))
		n /= 10;
	tmp[--size] = n + 48;
	if (sign)
		tmp[0] = '-';
	return (tmp);
}
