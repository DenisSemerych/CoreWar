/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_func_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 15:18:35 by dsemeryc          #+#    #+#             */
/*   Updated: 2019/01/13 19:34:27 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/printf.h"

void		print_stack(t_stack *stack)
{
	t_stack	*crawler;

	crawler = stack;
	while (crawler)
	{
		ft_printf("%d\n", crawler->data);
		crawler = crawler->next;
	}
	ft_printf("\n");
}

t_stack		*find_before_last(t_stack *head)
{
	t_stack *crawler;

	crawler = head;
	while (crawler && crawler->next && crawler->next->next)
		crawler = crawler->next;
	return (crawler);
}

t_stack		*find_max(t_stack *to_find)
{
	t_stack *max;

	max = to_find;
	while (to_find)
	{
		if (max->data < to_find->data)
			max = to_find;
		to_find = to_find->next;
	}
	return (max);
}

int			stack_size(t_stack *stack)
{
	t_stack	*crawler;
	int		size;

	crawler = stack;
	size = 0;
	while (crawler)
	{
		crawler = crawler->next;
		size++;
	}
	return (size);
}

t_stack		*find_last(t_stack *head)
{
	t_stack *crawler;

	crawler = head;
	while (crawler->next)
		crawler = crawler->next;
	return (crawler);
}
