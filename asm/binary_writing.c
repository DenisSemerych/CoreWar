/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_writing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 07:50:06 by dsemeryc          #+#    #+#             */
/*   Updated: 2019/03/27 10:47:56 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

unsigned				write_arg(unsigned char **file, t_inst *inst,
						t_list **lables, unsigned *champ_code)
{
	unsigned			tmp;
	unsigned			incr;

	if (inst->types[g_count] == T_REG && (incr = 1))
		(*file)[(g_written_bytes)++] =
			check_reg_num(spec_atoi(inst->args[g_count] + 1),
				inst->args[g_count]);
	else
	{
		if (!ft_strchr(inst->args[g_count], '%') &&
				!ft_strchr(inst->args[g_count], ':'))
			tmp = reverse_byte((unsigned)spec_atoi(inst->args[g_count]));
		else if (!ft_strchr(inst->args[g_count], ':'))
			tmp = reverse_byte((unsigned)spec_atoi(inst->args[g_count] + 1));
		else
			tmp = reverse_byte(give_label_address(lables, inst, champ_code));
		write_in_file(tmp, inst, &incr, file);
	}
	return (incr);
}

unsigned				write_argstype(unsigned char **file, t_inst *inst)
{
	int					count;
	unsigned char		code;

	count = 0;
	code = 0;
	while (count < 3)
	{
		if (inst->types[count] != T_IND && inst->types[count] != T_DIR &&
				inst->types[count] != T_REG)
			;
		else if (inst->types[count] == T_IND)
			code = code | IND_CODE;
		else if (inst->types[count] == T_DIR)
			code = code | DIR_CODE;
		else if (inst->types[count])
			code = code | REG_CODE;
		code = code << 2;
		count++;
	}
	(*file)[g_written_bytes++] = code;
	return (1);
}

void					write_champ_code(t_list *instructions,
						unsigned char **file, t_list **lables,
						unsigned *champ_code)
{
	int					index;
	t_inst				*inst;
	int					count;
	unsigned			incr;

	while (instructions)
	{
		incr = 0;
		count = -1;
		inst = instructions->content;
		index = give_op_index(inst->name);
		(*file)[g_written_bytes++] = g_op_tab[index].opcode;
		incr += 1;
		if (g_op_tab[index].octal)
			incr += write_argstype(file, inst);
		while (++count < inst->nb_arg)
		{
			g_count = count;
			incr += write_arg(file, inst, lables, champ_code);
		}
		*champ_code += incr;
		instructions = instructions->next;
	}
}

void					write_info(t_list *info,
						unsigned char **file, size_t code_size)
{
	t_list				*crawler;
	unsigned			size;

	crawler = info;
	while (crawler->content_size != NAME)
		crawler = crawler->next;
	if (ft_strlen(crawler->content) > PROG_NAME_LENGTH)
		error_function("Name more than PROG_NAME_LENGTH", NULL,
				crawler->content, 1);
	ft_memcpy((*file + g_written_bytes),
			crawler->content, ft_strlen(crawler->content));
	g_written_bytes += 132;
	size = reverse_byte(code_size);
	ft_memcpy(*file + g_written_bytes, &size, 4);
	crawler = info;
	g_written_bytes += 4;
	while (crawler->content_size != COMMENT)
		crawler = crawler->next;
	if (ft_strlen(crawler->content) > COMMENT_LENGTH)
		error_function("Comment more than COMMENT_LENGTH",
				NULL, crawler->content, 1);
	ft_memcpy(*file + g_written_bytes, crawler->content,
			ft_strlen(crawler->content));
	g_written_bytes += COMMENT_LENGTH + 4;
}

void					write_binary(t_list **arguments)
{
	unsigned char		*file;
	unsigned			tmp;
	int					fd;
	unsigned			champ_code;

	if ((fd = open(g_champ_name, O_RDWR | O_CREAT, 0666)) == -1)
		error_function("Error in opening file", NULL, g_champ_name, 1);
	tmp = reverse_byte(COREWAR_EXEC_MAGIC);
	g_written_bytes = 4;
	file = ft_memalloc(4 + 132 + COMMENT_LENGTH + 4 + 4);
	ft_memcpy(file, &tmp, g_written_bytes);
	write_info((*arguments)->next->next->content,
			&file, code_size((*arguments)->content));
	champ_code = 0;
	file = realloc(file, 4 + 132 + COMMENT_LENGTH + 4 + 4 + g_size);
	write_champ_code((*arguments)->content, &file,
			(t_list **)&(*arguments)->next->content, &champ_code);
	ft_printf("Writting output at %s\n", g_champ_name);
	write(fd, file, g_written_bytes);
	close(fd);
	free(file);
}
