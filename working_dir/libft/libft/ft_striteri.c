/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 21:12:27 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/10/29 17:35:22 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	ind;

	ind = 0;
	if (!s || !f)
		return ;
	while (s[ind])
	{
		f(ind, &s[ind]);
		ind++;
	}
}
