/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_functions2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 14:54:31 by dsemeryc          #+#    #+#             */
/*   Updated: 2019/03/11 14:22:51 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/printf.h"

void					free_str_arr(char **arr, int size)
{
	int					ind;

	ind = 0;
	while (ind < size)
		ft_strdel(&arr[ind++]);
	free(arr);
	arr = NULL;
}

int						count_size(char **arr)
{
	char				**tmp;
	int					size;

	size = 0;
	tmp = arr;
	while (tmp[size])
		size++;
	return (size);
}

void					check_for_add_sym(char *str)
{
	char				*tmp;

	tmp = str;
	while (*tmp)
		!ft_isdigit(*tmp) ?
			(put_err_msg_exit("Error: found non-integer symbol in coords/ants"))
			: tmp++;
}

int						spec_atoi(const char *str)
{
	char				*tmp;
	unsigned long int	num;

	num = 0;
	tmp = (char *)str;
	check_for_add_sym(tmp);
	while (*tmp > 47 && *tmp < 58)
	{
		num = (*tmp - 48) + (num * 10);
		if (num > 2147483647)
			put_err_msg_exit("Error: number more int-max value");
		tmp++;
	}
	return ((int)(num));
}

int						list_count(t_list *list)
{
	int count;

	count = 0;
	while (list)
	{
		count++;
		list = list->next;
	}
	return (count);
}
