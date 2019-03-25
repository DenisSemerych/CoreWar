/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_board.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochered <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 23:37:35 by yochered          #+#    #+#             */
/*   Updated: 2019/03/25 23:37:36 by yochered         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

static void	ft_puthex(unsigned char c)
{
	char *base;

	base = "0123456789abcdef";
	if (c < 16)
	{
		write(1, "0", 1);
		ft_putchar(base[c]);
	}
	else
	{
		ft_putchar(base[c / 16]);
		ft_putchar(base[c % 16]);
	}
}

static void	ft_do_it(unsigned char *p, size_t size)
{
	size_t n;

	n = -1;
	while (++n < 64)
	{
		if (n < size)
			ft_puthex(p[n]);
		else
		{
			write(1, "  ", 2);
			write(1, " ", 1);
		}
	}
	write(1, "\n", 1);
}

void		print_board(const void *addr, size_t size)
{
	unsigned char	*p;
	size_t			i;

	i = 0;
	p = (unsigned char*)addr;
	if (addr)
		while (i < size)
		{
			ft_printf("0x%04x : ", i);
			ft_do_it(&p[i], 64);
			i += 64;
		}
}
