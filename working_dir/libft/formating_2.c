/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formating_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 12:37:11 by dsemeryc          #+#    #+#             */
/*   Updated: 2019/01/13 18:26:43 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/printf.h"

void		set_to_zero(int *arr)
{
	int		i;

	i = 0;
	while (i < 8)
		arr[i++] = 0;
}

int			all_zeroes(char *str)
{
	while (*str)
	{
		if (*str != '0')
			return (0);
		str++;
	}
	return (1);
}

void		str_to_upper(char **str)
{
	char	*tmp;

	tmp = *str;
	while (*tmp)
	{
		ft_isalpha(*tmp) ? *tmp = ft_toupper(*tmp) : *tmp;
		tmp++;
	}
}

int			no_numbers(char *str)
{
	while (*str)
	{
		if (ft_isdigit(*str++))
			return (0);
	}
	return (1);
}

void		look_for_add_sym(char **str, int *arr, char p, int sign)
{
	if (p == 'p' || p == 'x' || p == 'X' || p == 'o' || p == 'O')
		octocorp(str, arr, p, "");
	if (p == 'd' || p == 'f' || p == 'i' || p == 'D' || p == 'F')
		extra_sign(str, arr, sign);
	if (p == 'X' || p == 'F')
		str_to_upper(str);
}
