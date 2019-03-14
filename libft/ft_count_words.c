/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 16:17:43 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/10/27 14:58:03 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(char *str, char c)
{
	int words;

	words = 0;
	while (*str == c)
		str++;
	while (*str)
	{
		if (*str == c && *(str - 1) != c)
			words++;
		str++;
	}
	if (*(str - 1) != c)
		words++;
	return (words);
}
