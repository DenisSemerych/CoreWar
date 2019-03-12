/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printmemory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 18:44:04 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/12/08 21:15:26 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void			ft_puthex(unsigned char n)
{
	char				*base;

	base = "0123456789abcdef";
	if (n < 16)
	{
		ft_putchar('0');
		ft_putchar(base[n]);
	}
	else
	{
		ft_putchar(base[n / 16]);
		ft_putchar(base[n % 16]);
	}
}

static	void			ft_print(unsigned char *add, size_t size)
{
	int					ind;

	ind = 0;
	while (ind < 16)
	{
		if (ind < (int)size)
			ft_puthex(add[ind]);
		else
			ft_putstr("  ");
		if (ind % 2 != 0)
			ft_putchar(' ');
		ind++;
	}
	ind = 0;
	while (ind < (int)size)
	{
		if (ft_isprint(add[ind]))
			ft_putchar(add[ind]);
		else
			ft_putchar('.');
		ind++;
	}
	ft_putchar('\n');
}

void					ft_print_memory(const void *addr, size_t size)
{
	unsigned char		*add;

	add = (unsigned char *)addr;
	if (!addr)
		return ;
	while (1)
	{
		if (size < 16)
		{
			ft_print(add, size);
			break ;
		}
		else
		{
			ft_print(add, 16);
			size = size - 16;
			add += 16;
		}
	}
}
