/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 12:32:50 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/10/24 13:26:08 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	unsigned long int	nb;
	int					digit;
	int					n;

	n = 0;
	nb = 0;
	digit = 1;
	while (ft_isspace(str[n]))
		n++;
	if (str[n] == '-')
		digit = -1;
	if (str[n] == '-' || str[n] == '+')
		n++;
	while (ft_isdigit(str[n]))
	{
		if ((nb > 922337203685477580 || (nb == 922337203685477580
			&& (str[n] - '0') > 7)) && digit == 1)
			return (-1);
		else if ((nb > 922337203685477580 || (nb == 922337203685477580
			&& (str[n] - '0') > 8)) && digit == -1)
			return (0);
		nb = nb * 10 + (str[n] - '0');
		n++;
	}
	return ((int)nb * digit);
}
