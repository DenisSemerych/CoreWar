/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insertion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 20:09:52 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/11/01 15:37:51 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		*ft_insertion(int *arr, int size)
{
	int	tmp;
	int	ind;
	int	tind;

	ind = 1;
	while (ind < size)
	{
		tind = ind;
		while (tind > 0 && arr[tind] < arr[tind - 1])
		{
			tmp = arr[tind - 1];
			arr[tind - 1] = arr[tind];
			arr[tind] = tmp;
			tind--;
		}
		ind++;
	}
	return (arr);
}
