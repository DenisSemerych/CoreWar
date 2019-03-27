/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 09:07:03 by dsemeryc          #+#    #+#             */
/*   Updated: 2019/03/27 19:04:38 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void			check_file(char *file, int *line_nbr)
{
	if (*file != COMMENT_CHAR && *file != ALT_COMMENT_CHAR &&
		!IS_SEPARATOR(*file) && *file != '.' && *file != '\n')
		error_function("Lexical error", line_nbr, file, 0);
}

t_list			*create_arg_list(t_list **lables,
				t_list *instructions, t_list *info)
{
	t_list		*new;

	if (!*lables && !instructions)
		error_function("Add at least one label",
				NULL, "No champ code and no label", 0);
	new = ft_lstnew(NULL, 0);
	new->next = ft_lstnew(NULL, 0);
	new->next->next = ft_lstnew(NULL, 0);
	new->content = instructions;
	new->content_size = 1;
	new->next->content = *lables;
	new->next->content_size = 2;
	new->next->next->content = info;
	new->next->next->content_size = 3;
	return (new);
}

void			cut_comment(char **line, char **file)
{
	char		*cut;

	cut = NULL;
	if (ft_strchr(*line, COMMENT_CHAR))
		cut = ft_strsub(*line, 0, ft_strchr(*file, COMMENT_CHAR) - *file);
	else if (ft_strchr(*line, ALT_COMMENT_CHAR))
		cut = ft_strsub(*line, 0, ft_strchr(*file, ALT_COMMENT_CHAR) - *file);
	if (cut)
	{
		free(*line);
		*line = cut;
	}
}

void			check_commas(char *line, int *line_nbr, int number)
{
	int			count;
	char		*crawler;

	count = 0;
	crawler = line;
	while (*crawler)
	{
		if (*crawler == SEPARATOR_CHAR)
			count++;
		crawler++;
	}
	if (count != number - 1)
		error_function("Syntax error", line_nbr, line, 1);
}

t_arg_type		define_type(char *command, int *line_nbr)
{
	t_arg_type	type;
	char		sym;

	sym = *command;
	if (sym == '%')
		type = T_DIR;
	else if (sym == 'r')
		type = T_REG;
	else
		type = T_IND;
	if (type == T_DIR)
		!ft_isdigit(*(ft_strchr(command, '%') + 1)) &&
			*(ft_strchr(command, '%') + 1) != ':' &&
			*(ft_strchr(command, '%') + 1) != '-' ?
			error_function("Syntax error", line_nbr, command, 1) :
			0;
	return (type);
}
