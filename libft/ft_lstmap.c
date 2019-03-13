/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 12:54:41 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/10/26 15:08:00 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*tmp;
	t_list	*tmp2;

	new = NULL;
	if (!lst || !f)
		return (NULL);
	while (lst)
	{
		if ((tmp = f(lst)))
		{
			if (new)
			{
				tmp2->next = tmp;
				tmp2 = tmp2->next;
			}
			else
			{
				new = tmp;
				tmp2 = new;
			}
		}
		lst = lst->next;
	}
	return (new);
}
