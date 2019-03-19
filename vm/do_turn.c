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

#include "vm.h"

extern t_op	g_op_tab[];

void		is_playing_check(t_data *data)
{
	t_list	*process;

	if (data->cycle_to_die <= 0)
		data->playing = 0;
	else
	{
		process = data->processes;
		while (process)
		{
			if (((t_process *)process->content)->live)
			{
				data->playing = 1;
				return;
			}
			process = process->next;
		}
		data->playing = 0;
	}
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
		if (((t_process *)process->content)->alive_cycle - data->cycle_to_die > 0)
			ft_lstdelcrt(&data->processes, process, NULL);
		process = process->next;
	}
	data->checks_amount++;
	if (data->live_op_amount >= NBR_LIVE || data->checks_amount >= MAX_CHECKS)
	{
		data->cycle_to_die -= CYCLE_DELTA;
		data->checks_amount = 0;
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
		if (!process->live)
			continue;
		if (!process->waiting_cycles)
		{
			process->op_code = data->board[process->position];
			if (process->op_code > 0 && process->op_code < 0x10)
				process->waiting_cycles = g_op_tab[process->op_code].cycles;
		}
		else
			process->waiting_cycles--;
		proc_p = proc_p->next;
	}
}

int 	op_args_size(t_process *process)
{
	int size;
	int i;

	size = 0;
	i = -1;
	while (++i < 3)
	{
		if (process->op_args_type[i] == T_REG)
			size++;
		else if (process->op_args_type[i] == T_IND)
			size += 2;
		else if (process->op_args_type[i] == T_DIR)
			size += g_op_tab[process->op_code].label;
	}
	return (size);
}

int 	check_process_args(t_process *process, t_data *data)
{
	int n;

	n = -1;
	while (++n < 3)
//		if (process->op_args_type[n] == T_REG && process->op_args[n] >= REG_NUMBER)
			return (0);
	return (1);

}

int 	check_process(t_process *process, t_data *data)
{
	if (process->op_code < 0 || process->op_code > 0x10)
		process->position++;
	else if (!check_process_args(process, data))
		process->position += 1 + g_op_tab[process->op_code].octal + op_args_size(process);
	else
		return (1);
	return (0);

}

void	execute_operations(t_data *data)
{
	t_list	*proc_p;
	t_process *process;

	proc_p = data->processes;
	while (proc_p)
	{
		process = proc_p->content;
		if (!process->waiting_cycles)
		{
			codage_proc(process, data->board[(process->position + 1) % MEM_SIZE]);
            if (process->op_code < 0 || process->op_code > 0x10)
                process->position++;
            else
            {
                execute_opeartion(proc_p->content, data);
                process->position += 1 + g_op_tab[process->op_code].octal + op_args_size(process);
            }
		}
		proc_p = proc_p->next;
	}
}

void	do_turn(t_data *data)
{
	while (data->playing)
	{
		read_operations(data);
		execute_operations(data);

		if (data->cycles_fr_lst_check >= data->cycle_to_die)
			to_die_check(data);
		is_playing_check(data);
		data->cycles_fr_lst_check++;
		data->cycle++;
	}
}