/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:26:28 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/10/25 15:01:16 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strequ(char const *s1, char const *s2)
{
	int n;

	if (!s1 || !s2)
		return (0);
	n = 0;
	while ((s1[n] != '\0') && s1[n] == s2[n])
		n++;
	n = (unsigned char)s1[n] - (unsigned char)s2[n];
	if (n != 0)
		return (0);
	else
		return (1);
}
