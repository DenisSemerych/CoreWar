/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 16:14:23 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/11/01 17:35:52 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		sign;

	sign = 1;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		sign = -1;
	}
	if (n > 9 || n < -9)
	{
		ft_putnbr_fd(((n / 10) * sign), fd);
		ft_putchar_fd((((n % 10) * sign) + 48), fd);
	}
	else
		ft_putchar_fd(((n * sign) + 48), fd);
}
