/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formating.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 12:40:27 by dsemeryc          #+#    #+#             */
/*   Updated: 2019/01/13 17:59:06 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/printf.h"

void				octocorp(char **str, int *arr, char c, char *tmp)
{
	if ((c != 'o' && c != 'O' && c != 'p') && no_numbers(*str))
		return ;
	if (c == 'p' && (tmp = ft_strjoin("0x", *str)))
	{
		free(*str);
		*str = tmp;
	}
	else if (arr[4] == '#' && ((ft_strlen(*str) == 1 || (all_zeroes(*str)
					&& (c == 'X' || c == 'x'))) && *str[0] == '0'))
		;
	else if (arr[4] == '#')
	{
		c == 'o' || c == 'O' ? (tmp = ft_strjoin("0", *str))
			: (tmp = ft_strjoin("0x", *str));
		free(*str);
		*str = tmp;
	}
	else if (!ft_strlen(*str) && arr[6] == 0 &&
			(c == 'o' || c == 'O') && arr[4] == '#')
	{
		tmp = ft_strjoin("0", *str);
		free(*str);
		*str = tmp;
	}
}

void				extra_sign(char **str, int *arr, int sign)
{
	char			ch;
	char			*tmp;
	char			*to_add;

	ch = (arr[2] == '+' ? '+' : ' ');
	if (sign == 1)
	{
		tmp = ft_strjoin("-", *str);
		free(*str);
		*str = tmp;
	}
	else if (arr[2] == '+' || arr[3] == ' ')
	{
		to_add = ft_memset(ft_strnew(1), ch, 1);
		tmp = ft_strjoin(to_add, *str);
		free(*str);
		free(to_add);
		*str = tmp;
	}
}

void				sub_formate(char **str, int *arr, int sign, char p)
{
	char			*tmp;
	char			*to_add;
	int				minus_number;
	int				whith;

	minus_number = sign;
	whith = arr[5];
	sign == 0 && (arr[2] == '+' || arr[3] == ' ') ? (sign = 1) : sign;
	look_for_add_sym(str, arr, p, minus_number);
	if (whith > (int)ft_strlen(*str))
	{
		to_add = ft_memset(ft_strnew(whith - ft_strlen(*str)),
				' ', whith - ft_strlen(*str));
		arr[0] == '-' ? (tmp = ft_strjoin(*str, to_add))
			: (tmp = ft_strjoin(to_add, *str));
		free(*str);
		free(to_add);
		*str = tmp;
	}
}

void				sub_formate2(char **str, int *arr, int sign, char p)
{
	char			*tmp;
	char			*to_add;
	int				minus_number;
	int				plus_sym;

	minus_number = sign;
	sign == 0 && (arr[2] == '+' || arr[3] == ' ') ? (sign = 1) : sign;
	NO_SIGN(p) && arr[1] == '0' ? (sign = 0) : sign;
	p == 'p' || ((p == 'x' || p == 'X' || p == 'o' || p == 'O')
			&& arr[4] == '#' && !all_zeroes(*str)) ? (plus_sym = 2)
		: (plus_sym = 0);
	p == 'o' && arr[4] == '#' ? (plus_sym = 1) : plus_sym;
	if (arr[5] > (int)ft_strlen(*str))
	{
		to_add = ft_memset(ft_strnew(arr[5] - ft_strlen(*str) - sign -
					plus_sym), '0', arr[5] -
				ft_strlen(*str) - sign - plus_sym);
		arr[0] == '-' ? (tmp = ft_strjoin(*str, to_add))
			: (tmp = ft_strjoin(to_add, *str));
		free(to_add);
		free(*str);
		*str = tmp;
	}
	look_for_add_sym(str, arr, p, minus_number);
}

int					formate(char *str, int *arr, char p, int sign)
{
	int				whith;
	int				padding_ch;

	whith = arr[5];
	padding_ch = ((arr[1] == 48 && arr[0] != '-') ? arr[1] : ' ');
	if (padding_ch != '0')
		sub_formate(&str, arr, sign, p);
	else
		sub_formate2(&str, arr, sign, p);
	ft_putstr(str);
	free(str);
	return ((int)ft_strlen(str));
}
