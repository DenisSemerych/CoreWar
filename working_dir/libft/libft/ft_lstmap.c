/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 18:27:52 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/11/01 19:21:54 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*crawler;

	if (!lst || !f)
		return ((t_list *)NULL);
	new = f(lst);
	lst = lst->next;
	crawler = new;
	while (lst)
	{
		crawler->next = f(lst);
		lst = lst->next;
		crawler = crawler->next;
	}
	return (new);
}
