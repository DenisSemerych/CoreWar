/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 20:00:58 by dsemeryc          #+#    #+#             */
/*   Updated: 2019/03/10 14:09:59 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

t_coord			*initialize_coord(int x, int y)
{
	t_coord		*new;

	if (!(new = (t_coord *)malloc(sizeof(t_coord))))
		return (NULL);
	new->next = NULL;
	new->x = x;
	new->y = y;
	return (new);
}

void			add_new(t_coord **coord, t_coord *elem)
{
	t_coord		*tmp;

	if (coord && elem)
	{
		tmp = *coord;
		*coord = elem;
		elem->next = tmp;
	}
}

void			free_lst(t_coord **coord)
{
	t_coord *tmp;
	t_coord *crawler;

	crawler = *coord;
	while (crawler)
	{
		tmp = crawler->next;
		free(crawler);
		crawler = tmp;
	}
	*coord = NULL;
}
