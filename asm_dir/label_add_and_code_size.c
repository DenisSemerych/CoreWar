/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_add_and_code_size.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 08:32:56 by dsemeryc          #+#    #+#             */
/*   Updated: 2019/03/27 10:28:35 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void			write_in_file(unsigned tmp, t_inst *inst,
				unsigned *incr, unsigned char **file)
{
	if (ft_strchr(inst->args[g_count], '%') &&
			g_op_tab[give_op_index(inst->name)].label == 4 &&
			(*incr = 4))
	{
		ft_memcpy(*file + g_written_bytes, &tmp, 4);
		g_written_bytes += 4;
	}
	else if ((*incr = 2))
	{
		tmp >>= 16;
		ft_memcpy(*file + g_written_bytes, &tmp, 2);
		g_written_bytes += 2;
	}
}

unsigned		label_address(t_list **labels, char *arg)
{
	t_lable		*lable;
	size_t		size_arg;
	size_t		size_lbl;
	t_list		*crawler;

	ft_strchr(arg, '%') ? (arg += 2) :
	(arg += 1);
	crawler = *labels;
	while (crawler)
	{
		size_arg = ft_strlen(arg);
		lable = crawler->content;
		size_lbl = ft_strlen(lable->name);
		if (ft_strnequ(arg, lable->name,
					size_lbl > size_arg ? size_lbl : size_arg))
			return (lable->opp ? lable->opp->lable->addr : g_size);
		crawler = crawler->next;
	}
	error_function("One of the labels invalid", NULL, arg, 1);
	return (0);
}

unsigned		give_label_address(t_list **lables,
				t_inst *inst, unsigned *champ_code)
{
	unsigned		add;

	add = label_address(lables, inst->args[g_count]);
	return (add - *champ_code);
}

void			init_in_code_size(int *index, t_inst **inst,
				size_t *current_size, int *i)
{
	*index = give_op_index((*inst)->name);
	*current_size = 0;
	*i = -1;
	(*inst)->nb_arg == 1 && (*inst)->types[0] == T_DIR ? 0 :
		(*current_size = *current_size + 1);
}

unsigned		code_size(t_list *instructions)
{
	int			index;
	size_t		current_size;
	t_inst		*inst;
	int			i;

	while (instructions)
	{
		inst = instructions->content;
		init_in_code_size(&index, &inst, &current_size, &i);
		while (i++ < inst->nb_arg)
		{
			if ((inst->types[i] == T_DIR && g_op_tab[index].label == 2) ||
					inst->types[i] == T_IND)
				current_size += 2;
			else if (inst->types[i] == T_DIR && g_op_tab[index].label == 4)
				current_size += 4;
			else
				current_size += 1;
		}
		inst->lable ? (inst->lable->addr = g_size) : 0;
		g_size += current_size;
		inst->size = current_size;
		instructions = instructions->next;
	}
	return (g_size);
}
