/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 23:37:50 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/03/26 00:10:21 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	zjmp(t_process *process, t_data *data)
{
	int value;

	value = read_arg(process, 0, data, INDIRECT);
	if (process->carry)
		process->position = get_absolute_cord(process->position, value %
				IDX_MOD);
	if (data->n_flag & 4)
		ft_printf("P %4d | zjmp %d %s\n", process->uniq_number, value,
				(process->carry) ? "OK" : "FAILED");
}

void	ldi_lldi(t_process *process, t_data *data)
{
	int pos1;
	int pos2;
	int reg;
	int offset;

	pos1 = read_arg(process, 0, data, INDIRECT);
	pos2 = read_arg(process, 1, data, INDIRECT);
	reg = read_arg(process, 2, data, DIRECT);
	offset = get_absolute_cord(process->position, (process->op_code == 10) ?
			((pos1 + pos2) % IDX_MOD) : (pos1 + pos2));
	if (data->n_flag & 4)
		ft_printf("P %4d | %s %d %d r%d\n       | -> load from %d + %d = %d (w"
				"ith pc%s %d)\n", process->uniq_number, (process->op_code == 10)
				? "ldi" : "lldi", pos1, pos2, reg, pos1, pos2, pos1 + pos2,
				(process->op_code == 10) ? " and mod" : "", offset);
	pos1 = -1;
	process->reg[reg] = 0;
	while (++pos1 < 4)
	{
		process->reg[reg] = (process->reg[reg] << 8) | data->board[offset];
		if (++offset >= MEM_SIZE)
			offset = 0;
	}
	if (process->op_code == 14)
		process->carry = (process->reg[reg] == 0);
}

void	sti(t_process *process, t_data *data)
{
	int from;
	int pos1;
	int pos2;
	int mod;
	int pos;

	from = read_arg(process, 0, data, DIRECT);
	pos1 = read_arg(process, 1, data, INDIRECT);
	pos2 = read_arg(process, 2, data, INDIRECT);
	mod = (pos1 + pos2) % IDX_MOD + process->position;
	if (data->n_flag & 4)
		ft_printf("P %4d | sti r%d %d %d\n       | -> store to %d + %d = %d"
			" (with pc and mod %d)\n", process->uniq_number, from, pos1,
			pos2, pos1, pos2, (pos1 + pos2), mod);
	pos = get_absolute_cord(process->position, (pos1 + pos2) % IDX_MOD);
	if (data->visual_flag && process)
		mark_data(data, pos, process->parent_number);
	write_data(&data->board[pos], read_arg(process, 0, data, INDIRECT), data);
}

void	fork_lfork(t_process *process, t_data *data)
{
	t_process	new_process;
	int			value;

	value = read_arg(process, 0, data, INDIRECT);
	value = (process->op_code == 12) ? (value % IDX_MOD) : value;
	ft_bzero(&new_process, sizeof(t_process));
	ft_memcpy(&new_process.reg, process->reg, sizeof(process->reg));
	new_process.uniq_number = ++data->max_process_num;
	new_process.carry = process->carry;
	new_process.alive_cycle = process->alive_cycle;
	new_process.position = get_absolute_cord(process->position, value);
	new_process.parent_number = process->parent_number;
	new_process.live = 1;
	ft_lstadd(&data->processes, ft_lstnew(&new_process, sizeof(t_process)));
	if (data->n_flag & 4)
		ft_printf("P %4d | %s %d (%d)\n", process->uniq_number,
				(process->op_code == 12) ? "fork" : "lfork", value,
				new_process.position);
}

void	aff(t_process *process, t_data *data)
{
	char	c;
	int		reg;

	c = read_arg(process, 0, data, INDIRECT);
	reg = read_arg(process, 0, data, DIRECT);
	if (data->n_flag & 4)
		ft_printf("P %4d | aff r%d: %c\n", process->uniq_number, reg, c);
	else if (data->a_flag)
		ft_printf("Aff: %c\n", c);
}
