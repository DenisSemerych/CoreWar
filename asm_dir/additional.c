/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 07:35:39 by dsemeryc          #+#    #+#             */
/*   Updated: 2019/03/27 10:20:23 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

unsigned int			reverse_byte(unsigned int num)
{
	unsigned			wrt;
	unsigned			byte;
	int					i;

	i = -1;
	wrt = 0;
	while (++i < 4)
	{
		byte = (num >> 8 * i) & 0xff;
		wrt |= byte << (24 - 8 * i);
	}
	return (wrt);
}

t_list					*find_last(t_list *head)
{
	t_list				*crawler;

	crawler = head;
	while (crawler && crawler->next)
		crawler = crawler->next;
	return (crawler);
}

t_list					*add_to_the_end_of_list(t_list *head, t_list *new)
{
	t_list				*crawler;

	crawler = head;
	if (!crawler)
		return (new);
	while (crawler->next)
		crawler = crawler->next;
	crawler->next = new;
	return (head);
}

void					check_for_add_sym(char *str)
{
	char				*tmp;

	tmp = str;
	if (*tmp == '-')
		tmp++;
	while (*tmp)
		!ft_isdigit(*tmp) ?
			(error_function("Lexical error", NULL, str, 0))
			: tmp++;
}

int						spec_atoi(const char *str)
{
	char				*tmp;
	unsigned long int	num;
	int					sign;

	num = 0;
	tmp = (char *)str;
	sign = ft_strchr(str, '-') ? -1 : 1;
	check_for_add_sym(tmp);
	while ((*tmp > 47 && *tmp < 58) || *tmp == '-')
	{
		if (*tmp != '-')
			num = (*tmp - 48) + (num * 10);
		tmp++;
	}
	return ((int)(num) * sign);
}
