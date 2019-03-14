/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 14:14:20 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/10/27 13:14:53 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	m;

	m = 0;
	if (n == 0)
		return (0);
	while (s1[m] != '\0' && s1[m] == s2[m] && (size_t)m < n - 1)
		m++;
	return ((unsigned char)s1[m] - (unsigned char)s2[m]);
}
