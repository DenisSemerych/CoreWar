/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_turn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 21:48:47 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/03/15 21:48:48 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	read_operations(t_data *data)
{
	t_list		*proc_p;
	t_process	*process;

	proc_p = data->processes;
	while (proc_p)
	{
		process = proc_p->content;
		if (!process->waiting_cycles && process->live)
		{
			process->op_code = data->board[process->position];
			if (process->op_code > 0 && process->op_code <= 0x10)
				process->waiting_cycles = g_op_tab[process->op_code].cycles;
		}
		if (process->live && process->op_code > 0 && process->op_code <= 0x10)
			process->waiting_cycles--;
		proc_p = proc_p->next;
	}
}

int		check_reg(t_process *process, t_data *data)
{
	int i;
	int reg;

	i = -1;
	while (++i < 3)
		if (process->op_args_type[i] == T_REG)
		{
			reg = read_arg(process, i, data, DIRECT);
			if (reg < 1 || reg > REG_NUMBER)
				return (0);
		}
	return (1);
}

void	exe2(t_data *data, t_process *process, int *n)
{
	int offset;

	offset = get_offset(process);
	if (data->n_flag & 16)
	{
		ft_printf("ADV %d (0x%04x -> 0x%04x)", offset,
				process->position, (process->position + offset) % MEM_SIZE);
		*n = -1;
		while (++(*n) < offset)
			ft_printf(" %02x", data->board[(process->position + *n)
			% MEM_SIZE]);
		ft_printf(" \n");
	}
	process->position = (process->position + offset) % MEM_SIZE;
}

void	execute_operations(t_data *data)
{
	t_list		*proc_p;
	t_process	*process;
	int			n;

	proc_p = data->processes;
	while (proc_p)
	{
		process = proc_p->content;
		if (!process->waiting_cycles)
		{
			if (process->op_code <= 0 || process->op_code > 0x10)
				process->position = (process->position + 1) % MEM_SIZE;
			else
			{
				codage_proc(process,
						data->board[(process->position + 1) % MEM_SIZE]);
				if ((n = write_args_pointers(data, process)) &&
					check_reg(process, data))
					execute_operation(proc_p->content, data);
				if (!(process->op_code == 9 && n && process->carry))
					exe2(data, process, &n);
			}
		}
		proc_p = proc_p->next;
	}
}

void	do_turn(t_data *data)
{
	if (data->n_flag & 2 && data->cycle)
		ft_printf("It is now cycle %d\n", data->cycle);
	read_operations(data);
	execute_operations(data);
	if (data->cycles_fr_lst_check >= data->cycle_to_die)
		to_die_check(data);
	if (data->dump_flag && data->cycle >= data->dump_cycles)
	{
		print_board(data->board, MEM_SIZE);
		exit(0);
	}
	if (!is_playing_check(data))
		return ;
	data->cycles_fr_lst_check++;
	data->cycle++;
}
