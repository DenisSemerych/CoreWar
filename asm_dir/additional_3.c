/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 07:47:29 by dsemeryc          #+#    #+#             */
/*   Updated: 2019/03/27 07:49:51 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void			skip_separators(char **file)
{
	while (IS_SEPARATOR(*(*file)))
		(*file)++;
}

void			skip_comment(char **file)
{
	if (IS_COMMENT(*(*file)))
	{
		while (*(*file) && *(*file) != '\n')
			(*file)++;
	}
}

int				is_free(char *line)
{
	while (line && *line)
	{
		if (!IS_SEPARATOR(*line))
			return (IS_COMMENT(*line) ? 1 : 0);
		line++;
	}
	return (1);
}

void			free_str_arr(char **arr, int size)
{
	int			ind;

	ind = 0;
	while (ind < size)
		ft_strdel(&arr[ind++]);
	free(arr);
}

int				count_size(char **arr)
{
	char		**tmp;
	int			size;

	size = 0;
	tmp = arr;
	while (tmp[size])
		size++;
	return (size);
}
