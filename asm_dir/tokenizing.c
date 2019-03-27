/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 08:53:06 by dsemeryc          #+#    #+#             */
/*   Updated: 2019/03/27 19:05:03 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void				init_lists(t_list **instructions,
					t_list **labels, t_list **info)
{
	*instructions = NULL;
	*labels = NULL;
	*info = NULL;
}

int					write_string_tokken(t_list *command, char **file,
					int *line_nbr)
{
	char			*crawler;
	int				size;
	char			*info;

	crawler = *file;
	size = 0;
	while (crawler && *crawler != '\"')
	{
		*crawler == '\n' ? (*line_nbr)++ : 0;
		crawler++;
		size++;
	}
	!crawler ? error_function("END (null) don`t close brackets",
				line_nbr, *file, 0) : size++;
	info = (char *)malloc(size);
	info[size - 1] = '\0';
	ft_strncpy(info, *file, size - 1);
	command->content = info;
	return (size);
}

void				save_info(char **file, t_list **info, int *line_nbr)
{
	t_list			*command;

	command = ft_lstnew(NULL, 0);
	if (!ft_strncmp(*file, NAME_CMD_STRING, 5) && (*file = *file + 5))
		command->content_size = NAME;
	else if (!ft_strncmp(*file, COMMENT_CMD_STRING, 8) && (*file = *file + 8))
		command->content_size = COMMENT;
	else
		error_function("Not supported command", line_nbr, *file, 0);
	skip_separators(file);
	*(*file) != '\"' ? error_function("Error in command line",
						line_nbr, *file, 0) : ((*file)++);
	*file = *file + write_string_tokken(command, file, line_nbr);
	ft_lstadd(info, command);
}

void				save_instruction(char **file, t_list **instructions,
					t_list **lables, int *line_nbr)
{
	t_op			*op;
	char			*line;
	char			*crawler;

	line = ft_strsub(*file, 0, ft_strchr(*file, '\n') - *file);
	cut_comment(&line, file);
	crawler = line;
	if (is_label(crawler, line_nbr))
		crawler += validate_lable(lables, crawler, line_nbr);
	if (is_free(crawler))
	{
		*file += crawler - line;
		free(line);
		return ;
	}
	op = find_op(&crawler);
	if (!op)
		error_function("Syntax error", line_nbr, *file, 0);
	*instructions = add_to_the_end_of_list(*instructions,
					validate_command(op, line_nbr, crawler));
	give_op_lable(find_last(*instructions), lables);
	*file += ft_strlen(line);
	free(line);
}

t_list				*tokenize(char *file)
{
	int				line_nbr;
	t_list			*instructions;
	t_list			*labels;
	t_list			*info;

	init_lists(&instructions, &labels, &info);
	line_nbr = 1;
	while (*file)
	{
		if (*file == '.')
			save_info(&file, &info, &line_nbr);
		skip_separators(&file);
		*file == '\n' && *file++ ? line_nbr++ : 0;
		skip_comment(&file);
		if (*file != '\0' && ft_strchr(file, '\n'))
			full(info) ? save_instruction(&file, &instructions, &labels,
					&line_nbr) :
				check_file(file, &line_nbr);
		else if (*file != '\0' && !ft_strchr(file, '\n')
				&& !ft_strchr(file, COMMENT_CHAR) &&
				!ft_strchr(file, ALT_COMMENT_CHAR) && !IS_SEPARATOR(*file))
			error_function("Missing newline after instruction", NULL, file, 1);
		skip_separators(&file);
	}
	return (create_arg_list(&labels, instructions, info));
}
