/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 12:22:19 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/10/31 12:44:55 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_pow(int num, int pow)
{
	int	result;

	if (pow > 2)
		result = num * ft_pow(num, pow - 1);
	else
		result = num * num;
	return (result);
}
