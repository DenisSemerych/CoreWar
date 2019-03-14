/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 12:43:34 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/10/26 13:25:06 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	t_list *buf;

	if (alst)
	{
		if (*alst)
		{
			buf = *alst;
			*alst = new;
			new->next = buf;
		}
		else
			*alst = new;
	}
}
