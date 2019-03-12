/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 18:15:42 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/11/01 19:22:10 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list	*crawler;

	if (!lst || !f)
		return ;
	crawler = lst;
	while (crawler->next)
	{
		f(crawler);
		crawler = crawler->next;
	}
	f(crawler);
}
