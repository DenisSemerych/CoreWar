/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_auxiliary.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochered <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 00:35:29 by yochered          #+#    #+#             */
/*   Updated: 2019/03/26 00:35:30 by yochered         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		read_arg(t_process *process, int argnum, t_data *data, int dir_flag)
{
	int				arg;
	int				size;
	int				n;
	unsigned char	*p;

	n = -1;
	arg = 0;
	p = process->op_args_pointers[argnum];
	size = get_type_size(process, process->op_args_type[argnum]);
	if (dir_flag == INDIRECT && process->op_args_type[argnum] == T_IND)
	{
		size = 4;
		p = get_t_ind_pointer(data, process, argnum);
	}
	while (++n < size)
	{
		arg <<= 8;
		arg |= (int)*p++;
		if (p - data->board >= MEM_SIZE)
			p = data->board;
	}
	arg = (size == 2) ? (short)arg : arg;
	arg = ((dir_flag == INDIRECT && process->op_args_type[argnum] == T_REG)
			? process->reg[arg] : arg);
	return (arg);
}

void	write_data(void *position, unsigned int value, t_data *data)
{
	int				n;
	unsigned char	*p;

	n = 0;
	p = position;
	while (n < 4)
	{
		*p++ = (value & 0xFF000000) >> 24;
		value <<= 8;
		if (p - data->board >= MEM_SIZE)
			p = data->board;
		n++;
	}
}

void	mark_data(t_data *data, int pos, int owner)
{
	int i;

	i = -1;
	while (++i < 4)
	{
		if (pos >= MEM_SIZE)
			pos = 0;
		data->vs->map[pos].owner = owner;
		data->vs->map[pos].cycles_after_st = data->cycle + 50;
		pos++;
	}
}

void	execute_opeartion(t_process *process, t_data *data)
{
	static void (*exec_op[17])(t_process*, t_data*);

	if (!exec_op[1])
	{
		exec_op[1] = live;
		exec_op[2] = ld_lld;
		exec_op[3] = st;
		exec_op[4] = sub_add;
		exec_op[5] = sub_add;
		exec_op[6] = and_or_xor;
		exec_op[7] = and_or_xor;
		exec_op[8] = and_or_xor;
		exec_op[9] = zjmp;
		exec_op[10] = ldi_lldi;
		exec_op[11] = sti;
		exec_op[12] = fork_lfork;
		exec_op[13] = ld_lld;
		exec_op[14] = ldi_lldi;
		exec_op[15] = fork_lfork;
		exec_op[16] = aff;
	}
	exec_op[process->op_code](process, data);
}
