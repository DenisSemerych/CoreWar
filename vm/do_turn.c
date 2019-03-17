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
	t_list	*process;

	process = data->processes;
	while (process)
	{
		if (!((t_process*)process->content)->live)
			continue;
		if (!((t_process*)process->content)->waiting_cycles)
			((t_process*)process->content)->op_code = data->board[((t_process*)process->content)->position];
		else
			((t_process*)process->content)->waiting_cycles--;
		process = process->next;
	}
}

void	do_turn(t_data *data)
{
	t_list	*process;

	while (data->playing)
	{
		read_operations(data);
		process = data->processes;
		while (process)
		{

			process = process->next;
		}

		if (data->cycles_fr_lst_check >= data->cycle_to_die)
			to_die_check(data);
		is_playing_check(data);
		data->cycles_fr_lst_check++;
		data->cycle++;
	}
}