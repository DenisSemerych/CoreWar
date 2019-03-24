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

int		is_playing_check(t_data *data)
{
	t_list	*process;

	if (data->cycle_to_die <= 0 || !data->processes)
		data->playing = 0;
	else
	{
		process = data->processes;
		while (process)
		{
			if (((t_process *)process->content)->live)
				return (data->playing = 1);
			process = process->next;
		}
		data->playing = 0;
	}
	return (data->playing);
}

void	ft_lstdelcrt(t_list **list, t_list *to_delete, void (*del)(void *, size_t))
{
	t_list	*p;

	if (!(list || *list || to_delete))
		return;
	if (*list == to_delete)
		*list = to_delete->next;
	else
	{
		p = *list;
		while (p->next != to_delete)
			p = p->next;
		p->next = to_delete->next;
	}
	if (del)
		del(to_delete->content, to_delete->content_size);
	free(to_delete);
}

void	to_die_check(t_data *data)
{
	t_list	*process;

	process = data->processes;
	while (process)
	{
		if (data->cycle - ((t_process *)process->content)->alive_cycle >= data->cycle_to_die)
		{
			if (data->n_flag & 8)
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", ((t_process*)process->content)->uniq_number, data->cycle - ((t_process*)process->content)->alive_cycle, data->cycle_to_die);
			ft_lstdelcrt(&data->processes, process, NULL);
		}
		process = process->next;
	}
	data->checks_amount++;
	if (data->live_op_amount >= NBR_LIVE || data->checks_amount >= MAX_CHECKS)
	{
		data->cycle_to_die -= CYCLE_DELTA;
		data->checks_amount = 0;
		if (data->n_flag & 2)
			ft_printf("Cycle to die is now %d\n", data->cycle_to_die);
	}
	data->cycles_fr_lst_check = 0;
	data->live_op_amount = 0;
}

void	read_operations(t_data *data)
{
	t_list	*proc_p;
	t_process *process;

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

int	check_reg(t_process *process, t_data *data)
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



void	execute_operations(t_data *data)
{
	t_list	*proc_p;
	t_process *process;
	int			offset;
	int			n;

	if (data->cycle >= 848)
	{
		int i = 25;
		process = process;
	}

	proc_p = data->processes;
	while (proc_p)
	{
		process = proc_p->content;
		if (!process->waiting_cycles)
		{
			codage_proc(process, data->board[(process->position + 1) % MEM_SIZE]);
			if (process->op_code <= 0 || process->op_code > 0x10)
				process->position = (process->position + 1) % MEM_SIZE;
			else
			{
				if ((n = write_args_pointers(data, process)) && check_reg(process, data))
					execute_opeartion(proc_p->content, data);
				if (!(process->op_code == 9 && n && process->carry))
				{
					offset = get_offset(process);
					if (data->n_flag & 16)
					{
						ft_printf("ADV %d (%#06x -> %#06x)", offset, process->position, (process->position + offset) % IDX_MOD);
						n = -1;
						while (++n < offset)
							ft_printf(" %02x", data->board[(process->position + n) % MEM_SIZE]);
						ft_printf("\n");
					}
                	process->position = (process->position + offset) % MEM_SIZE;
				}
			}
		}
		proc_p = proc_p->next;
	}
}

void	do_turn(t_data *data)
{
	if (data->n_flag & 2 && data->cycle)
		ft_printf("It is now cycle %d\n", data->cycle);
	if (data->cycles_fr_lst_check >= data->cycle_to_die)
		to_die_check(data);
	read_operations(data);
	execute_operations(data);
	if (!is_playing_check(data))
		return ;
	data->cycles_fr_lst_check++;
	data->cycle++;
}