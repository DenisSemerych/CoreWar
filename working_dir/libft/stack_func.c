/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 15:15:43 by dsemeryc          #+#    #+#             */
/*   Updated: 2019/01/13 19:34:16 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/printf.h"

void		swap(t_stack **stack_one, t_stack **stack_two)
{
	int		tmp;
	t_stack	*stack_a;

	stack_a = *stack_one;
	if (stack_a && stack_a->next)
	{
		tmp = stack_a->data;
		stack_a->data = stack_a->next->data;
		stack_a->next->data = tmp;
	}
	if (stack_two)
		swap(stack_two, NULL);
}

void		push(t_stack **stack_one, t_stack **stack_two)
{
	t_stack *elem;

	if (*stack_two)
	{
		elem = *stack_two;
		*stack_two = elem->next;
		elem->next = *stack_one;
		*stack_one = elem;
	}
}

void		rotate(t_stack **head, t_stack **head_b)
{
	t_stack	*tail;
	t_stack	*tmp;

	if (*head && (*head)->next)
	{
		tail = *head;
		*head = tail->next;
		tmp = find_last(*head);
		tmp->next = tail;
		tail->next = NULL;
	}
	if (head_b)
		rotate(head_b, NULL);
}

void		rev_rotate(t_stack **head, t_stack **head_b)
{
	t_stack	*tail;
	t_stack	*new_tail;

	if (*head && (*head)->next)
	{
		tail = find_last(*head);
		new_tail = find_before_last(*head);
		tail->next = *head;
		new_tail->next = NULL;
		*head = tail;
	}
	if (head_b)
		rev_rotate(head_b, NULL);
}

t_stack		*create_stack(int *data, int size)
{
	t_stack	*head;
	t_stack	*crawler;
	int		ind;

	ind = 0;
	head = (t_stack *)malloc(sizeof(t_stack *));
	head->data = data[ind++];
	crawler = head;
	while (ind < size)
	{
		crawler->next = (t_stack *)malloc(sizeof(t_stack *));
		crawler = crawler->next;
		crawler->data = data[ind++];
	}
	crawler->next = NULL;
	return (head);
}
