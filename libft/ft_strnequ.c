/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:26:28 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/10/26 14:00:54 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t	m;

	m = 0;
	if (!s1 || !s2)
		return (0);
	if (n == 0)
		return (1);
	while (s1[m] != '\0' && s1[m] == s2[m] && m < n - 1)
		m++;
	m = (unsigned char)s1[m] - (unsigned char)s2[m];
	if (m != 0)
		return (0);
	else
		return (1);
}
