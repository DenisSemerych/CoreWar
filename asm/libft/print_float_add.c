/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 19:12:45 by dsemeryc          #+#    #+#             */
/*   Updated: 2019/01/13 18:28:53 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/printf.h"

int				give_index(char *str, int percision)
{
	int			index;
	int			check_dot;

	index = 0;
	check_dot = 0;
	while (str[index] && percision)
	{
		if (check_dot)
			percision--;
		if (str[index] == '.')
			check_dot = 1;
		index++;
	}
	return (index);
}

void			add_zeros(char **str, int percision, int i)
{
	char		*tmp;
	char		*to_add;

	to_add = ft_memset(ft_strnew(percision - (ft_strlen(*str) - i)),
			'0', percision - (ft_strlen(*str) - i));
	tmp = ft_strjoin(*str, to_add);
	free(to_add);
	free(*str);
	*str = tmp;
}

int				get_sign(double num)
{
	uint64_t	*data;

	data = (void *)&num;
	return (*data >> 63 & 1 ? 1 : 0);
}

int				is_nan_or_inf(char **tmp, long double num, int *arr)
{
	if (num == 0.0 / 0.0 && (arr[1] = ' ') &&
			(arr[2] = 0))
	{
		*tmp = ft_strdup("nan");
		return (1);
	}
	else if (num == 1.0 / 0 && (arr[1] = ' '))
	{
		*tmp = ft_strdup("inf");
		return (1);
	}
	return (0);
}
