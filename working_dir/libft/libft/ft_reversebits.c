/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reversebits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 18:35:09 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/10/29 18:40:49 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned char	ft_reversed_bits(unsigned char octet)
{
	int	base;
	int	result;

	base = 256;
	result = 0;
	while (octet != 0)
	{
		result += (octet & 1) * (base >>= 1);
		octet >>= 1;
	}
	return (result);
}
