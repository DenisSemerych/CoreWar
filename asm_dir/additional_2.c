/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 07:41:22 by dsemeryc          #+#    #+#             */
/*   Updated: 2019/03/27 07:47:21 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

t_op			*find_op(char **crawler)
{
	int			count;
	size_t		size;
	t_op		*op;

	count = 0;
	skip_separators(crawler);
	op = NULL;
	while (count++ < 16)
	{
		size = ft_strlen(g_op_tab[count].name);
		if (ft_strnequ(*crawler, g_op_tab[count].name, size))
			op = &g_op_tab[count];
	}
	return (op);
}

unsigned char	check_reg_num(int num, char *arg)
{
	if (num > 99)
		error_function("Wrong reg number", NULL, arg, 1);
	return (num);
}

int				give_op_index(char *op_name)
{
	int			count;

	count = 0;
	while (++count < 16)
	{
		if (ft_strequ(op_name, g_op_tab[count].name))
			break ;
	}
	return (count);
}

int				is_label(char *line, int *line_nbr)
{
	char		*crawler;

	crawler = line;
	while (crawler && *crawler)
	{
		if (!ft_strchr(LABEL_CHARS, *crawler))
			break ;
		crawler++;
	}
	if (ft_strchr(line, ':') && !ft_strchr(line, DIRECT_CHAR) &&
			!ft_strchr(line, SEPARATOR_CHAR)
			&& crawler && *crawler != ':')
		error_function("Wrong char in lable name", line_nbr, line, 1);
	return (crawler && *crawler == LABEL_CHAR ? 1 : 0);
}

int				full(t_list *info)
{
	char		count_comment;
	char		count_name;
	t_list		*name;
	t_list		*comment;

	count_name = 0;
	count_comment = 0;
	while (info)
	{
		if (info->content_size == NAME && (name = info))
			count_name++;
		else if (info->content_size == COMMENT && (comment = info))
			count_comment++;
		info = info->next;
	}
	if (count_name > 1)
		error_function(".name command need to be only one", NULL,
				name->content, 0);
	else if (count_comment > 1)
		error_function(".comment command need to be only one", NULL,
				comment->content, 0);
	return (count_comment + count_name == 2 ? 1 : 0);
}
