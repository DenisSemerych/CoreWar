/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 21:13:28 by dsemeryc          #+#    #+#             */
/*   Updated: 2019/01/13 18:28:39 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/printf.h"

void			make_it_round(char **str, int percision, int *i)
{
	int			index;
	int			extra_one;
	char		*tmp;

	tmp = *str;
	percision == 0 || percision > 6 ? (index = ft_strlen(tmp) - 1)
		: (index = give_index(tmp, percision));
	tmp[index--] > '5' ? (extra_one = 1)
		: (extra_one = 0);
	while (tmp[index] && extra_one)
	{
		tmp[index] == '.' ? index-- : index;
		if ((tmp[index] += extra_one) > '9')
		{
			tmp[index] = '0';
			if (index == 0 && (tmp = ft_strjoin("1", tmp)) && (*i += 1))
			{
				free(*str);
				*str = tmp;
			}
		}
		else
			extra_one = 0;
		index--;
	}
}

char			*make_cnv_float(char *num, long double fl, int percision)
{
	char		*str;
	int			i;
	char		*tmp;

	i = 0;
	str = ft_strnew(percision);
	while (i < percision + 1)
	{
		str[i++] = (int)(fl * 10) + '0';
		fl *= 10;
		fl -= (int)fl;
	}
	str[i] = '\0';
	i = ft_strlen(num);
	tmp = ft_strjoin(num, str);
	free(str);
	str = tmp;
	make_it_round(&str, percision, &i);
	ft_bzero(str + i + percision, ft_strlen(str + i + percision));
	if ((int)(ft_strlen(str) - i) < percision)
		add_zeros(&str, percision, i);
	return (str);
}

void			set_string(char **tmp, __uint128_t i_part, int *arr)
{
	char		*str;

	if (arr[6] != 0 || arr[4] == '#')
	{
		str = ft_itoa_uint128(i_part);
		*tmp = ft_strjoin(str, ".");
		free(str);
	}
	else
	{
		str = ft_itoa_uint128(i_part);
		*tmp = str;
	}
}

int				print_float(long double num, int *arr, char c)
{
	__uint128_t	i_part;
	long double	f_part;
	char		*tmp;
	int			sign;
	char		*ret;

	if (num == 0.0 && (sign = get_sign((double)num)) == 1)
		num *= -1;
	else
		num < 0 && (num *= -1) ? (sign = 1) :
			(sign = 0);
	if (is_nan_or_inf(&tmp, num, arr) == 1)
		return (formate(tmp, arr, c, sign));
	else
	{
		if (arr[6] == -42)
			arr[6] = 6;
		i_part = (__uint128_t)num;
		f_part = (num - i_part);
		set_string(&tmp, i_part, arr);
		ret = make_cnv_float(tmp, f_part, arr[6]);
		free(tmp);
		tmp = ret;
	}
	return (formate(tmp, arr, c, sign));
}
