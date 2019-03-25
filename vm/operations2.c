/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochered <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 00:37:40 by yochered          #+#    #+#             */
/*   Updated: 2019/03/26 00:37:41 by yochered         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	live(t_process *process, t_data *data)
{
	int		champ_num;
	t_list	*champ_p;

	champ_num = read_arg(process, 0, data, INDIRECT);
	process->alive_cycle = data->cycle;
	data->live_op_amount++;
	champ_p = data->champs;
	if (data->n_flag & 4)
		ft_printf("P %4d | live %d\n", process->uniq_number, champ_num);
	else if (data->visual_flag && data->vs)
		data->vs->map[process->position].cycles_after_live = data->cycle + 50;
	champ_num *= -1;
	while (champ_p)
	{
		if (((t_champ*)champ_p->content)->number == champ_num)
		{
			data->last_alive_champ = champ_num;
			if (data->n_flag & 1)
				ft_printf("Player %d (%s) is said to be alive\n", champ_num,
						((t_champ*)champ_p->content)->name);
			return ;
		}
		champ_p = champ_p->next;
	}
}

void	st(t_process *process, t_data *data)
{
	int				what;
	int				from;
	int				where;
	unsigned char	*pos;

	what = read_arg(process, 0, data, INDIRECT);
	from = read_arg(process, 0, data, DIRECT);
	where = read_arg(process, 1, data, DIRECT);
	if (process->op_args_type[1] == T_REG)
		process->reg[where] = what;
	else
	{
		pos = get_t_ind_pointer(data, process, 1);
		if (pos && data->visual_flag && data->vs)
			mark_data(data, pos - data->board, process->parent_number);
		write_data(pos, what, data);
	}
	if (data->n_flag & 4)
		ft_printf("P %4d | st r%d %s%d\n", process->uniq_number, from,
				(process->op_args_type[1] == T_REG) ? "r" : "", where);
}

void	ld_lld(t_process *process, t_data *data)
{
	int value;
	int ind;

	value = read_arg(process, 0, data, INDIRECT);
	ind = read_arg(process, 1, data, DIRECT);
	process->reg[ind] = value;
	process->carry = (value == 0);
	if (data->n_flag & 4)
		ft_printf("P %4d | %s %d r%d\n", process->uniq_number,
				(process->op_code == 2) ? "ld" : "lld", value, ind);
}

void	sub_add(t_process *process, t_data *data)
{
	int r1;
	int r2;
	int r3;
	int value1;
	int value2;

	r1 = read_arg(process, 0, data, DIRECT);
	r2 = read_arg(process, 1, data, DIRECT);
	r3 = read_arg(process, 2, data, DIRECT);
	value1 = read_arg(process, 0, data, INDIRECT);
	value2 = read_arg(process, 1, data, INDIRECT);
	value1 = (process->op_code == 4) ? (value1 + value2) : (value1 - value2);
	process->reg[r3] = value1;
	process->carry = (read_arg(process, 2, data, INDIRECT) == 0);
	if (data->n_flag & 4)
		ft_printf("P %4d | %s r%d r%d r%d\n", process->uniq_number,
				(process->op_code == 4) ? "add" : "sub", r1, r2, r3);
}

void	and_or_xor(t_process *process, t_data *data)
{
	int		value1;
	int		value2;
	int		where;
	char	*operation;

	value1 = read_arg(process, 0, data, INDIRECT);
	value2 = read_arg(process, 1, data, INDIRECT);
	where = read_arg(process, 2, data, DIRECT);
	if (process->op_code == 6)
		operation = "and";
	else
		operation = (process->op_code == 7) ? "or" : "xor";
	if (process->op_code == 6)
		process->reg[where] = value1 & value2;
	else
		process->reg[where] = (process->op_code == 7) ? (value1 | value2) :
			(value1 ^ value2);
	process->carry = (process->reg[where] == 0);
	if (data->n_flag & 4)
		ft_printf("P %4d | %s %d %d r%d\n", process->uniq_number, operation,
				value1, value2, where);
}
