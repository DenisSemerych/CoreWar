/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printbits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 17:58:52 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/10/31 12:51:24 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_bits(unsigned char octet)
{
	int	div;

	div = 128;
	while (div != 1)
	{
		if (octet / div == 1)
			ft_putchar('1');
		else
			ft_putchar('0');
		octet = octet % div;
		div /= 2;
	}
	if (octet == 1)
		ft_putchar('1');
	else
		ft_putchar('0');
}
