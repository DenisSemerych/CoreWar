/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 13:28:25 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/10/24 15:59:15 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memset(void *b, int c, size_t len)
{
	char	*tmp;

	tmp = b;
	while (len)
	{
		*tmp = (unsigned char)c;
		tmp++;
		len--;
	}
	return (b);
}
