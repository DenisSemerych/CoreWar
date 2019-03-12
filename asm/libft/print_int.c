/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 20:13:31 by dsemeryc          #+#    #+#             */
/*   Updated: 2019/01/13 18:29:05 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/printf.h"

int			print_pointer(void *pointer, int *arr)
{
	char	*tmp;

	tmp = ibull((unsigned long)pointer, 16, arr[6]);
	make_int_cnv(&tmp, arr, 'p');
	return (formate(tmp, arr, 'p', 0));
}

int			print_char(char ch, int *arr)
{
	char	*tmp;
	char	padding_ch;
	int		whith;

	if (ch != 0)
		return (formate(ft_memset(ft_strnew(1), ch, 1), arr, 'c', 0));
	tmp = NULL;
	padding_ch = ((arr[1] == 48 && arr[0] != '-') ? arr[1] : ' ');
	whith = arr[5];
	if (whith > 1)
	{
		tmp = ft_memset(ft_strnew(whith - 1), padding_ch, whith - 1);
		arr[0] == '-' ? write(1, &ch, 1) && write(1, tmp, whith - 1)
			: write(1, tmp, whith - 1) && write(1, &ch, 1);
	}
	else
		write(1, &ch, 1);
	return (tmp ? (int)ft_strlen(tmp) + 1 : 1);
}

void		make_int_cnv(char **str, int *arr, char c)
{
	int		oct;
	char	*tmp;
	char	*to_add;

	oct = ((c == 'o' || c == 'O') && arr[4] == '#' ? 1 : 0);
	if (arr[6] != -42 && arr[1] == '0')
		arr[1] = 0;
	if (arr[6] == -42)
		arr[6] = 0;
	if (arr[6] > (int)ft_strlen(*str))
	{
		to_add = ft_memset(ft_strnew(arr[6] - ft_strlen(*str) - oct),
				'0', arr[6] - ft_strlen(*str) - oct);
		tmp = ft_strjoin(to_add, *str);
		free(*str);
		free(to_add);
		*str = tmp;
	}
}

void		what_base(int *base, char c)
{
	if (c == 'o' || c == 'x' || c == 'X' || c == 'O')
		c == 'o' || c == 'O' ? (*base = 8) :
			(*base = 16);
	else
		*base = 10;
}

int			print_int(void *num, char c, int *arr, int sign)
{
	int		base;
	char	*str;

	if (c == 'c')
		return (print_char((char)num, arr));
	what_base(&base, c);
	if ((c == 'u' || c == 'U' || base == 16 || base == 8) &&
		(arr[7] == 216 || arr[7] == 108 || c == 'U' || c == 'O'))
		str = ibull((unsigned long long)num, base, arr[6]);
	else if ((c == 'u' || base == 16 || base == 8) &&
			(arr[7] == 208 || arr[7] == 104))
		arr[7] == 208 ? (str = ibull((unsigned char)num, base, arr[6]))
			: (str = ibull((unsigned short)num, base, arr[6]));
	else if (c == 'u' || base == 16 || base == 8)
		str = ibull((unsigned int)num, base, arr[6]);
	else if (arr[7] == 108 || arr[7] == 216 || c == 'D')
		arr[7] == 108 ? (str = ibl((long)num, base, &sign, arr[6]))
			: (str = ibl((long long)num, base, &sign, arr[6]));
	else if (arr[7] == 104 || arr[7] == 208)
		arr[7] == 104 ? (str = ibl((short)num, base, &sign, arr[6]))
			: (str = ibl((signed char)num, base, &sign, arr[6]));
	else
		str = ibl((int)num, base, &sign, arr[6]);
	make_int_cnv(&str, arr, c);
	return (formate(str, arr, c, sign));
}
