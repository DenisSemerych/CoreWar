/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 10:42:55 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/10/29 16:11:47 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	while (++n < 16)
	{
		if (n < size)
			ft_puthex(p[n]);
		else
			write(1, "  ", 2);
		if (n % 2 != 0)
			write(1, " ", 1);
	}
	n = -1;
	while (++n < size)
		if (p[n] >= ' ' && p[n] <= '~')
			write(1, &p[n], 1);
		else
			write(1, ".", 1);
	write(1, "\n", 1);
}

void		ft_print_memory(const void *addr, size_t size)
{
	unsigned char *p;

	p = (unsigned char*)addr;
	if (addr)
		while (size != 0)
		{
			if (size >= 16)
			{
				ft_do_it(p, 16);
				size -= 16;
				p += 16;
			}
			else
			{
				ft_do_it(p, size);
				size = 0;
			}
		}
}
