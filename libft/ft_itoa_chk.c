/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_chk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 13:25:29 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/02/06 13:26:53 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_itoa_chk(char *string, int number)
{
	char *test;

	test = ft_itoa(number);
	number = (!ft_strcmp(string, test)) ? 1 : 0;
	free(test);
	return (number);
}
