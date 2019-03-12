/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:25:53 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/11/01 15:31:58 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int						ft_atoi(const char *str)
{
	char				*tmp;
	unsigned long int	num;
	int					isn;

	num = 0;
	isn = 1;
	tmp = (char *)str;
	if (*tmp == '\200' || *tmp == '\0')
		return (0);
	while ((*tmp < 33 || *tmp > 126) && *tmp != '\e')
		tmp++;
	if (*tmp == 45)
		isn = -1;
	if (*tmp == 45 || *tmp == 43)
		tmp++;
	while (*tmp > 47 && *tmp < 58)
	{
		num = (*tmp - 48) + (num * 10);
		if (num >= 9223372036854775807 && isn == 1)
			return (-1);
		else if (num > 9223372036854775807 && isn == -1)
			return (0);
		tmp++;
	}
	return ((int)(num * isn));
}
