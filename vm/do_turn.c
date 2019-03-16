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

int		is_playing(t_data *data)
{
	t_list	*process;

	if (data->cycle_to_die <= 0)
		return (0);
	process = data->processes;
	while (process)
	{
		if (((t_process *)process->content)->live)
			return (1);
		process = process->next;
	}
	return (0);
}

void	check_processes_alive(t_data *data)
{
	t_list	*process;

	process = data->processes;
	while (process)
	{
		if (!((t_process *)process->content)->live)
			continue;
		if (((t_process *)process->content)->alive_cycle - data->cycle_to_die > 0)
			((t_process *)process->content)->live = 0;
		process = process->next;
	}
}

void	do_turn(t_data *data)
{
	t_list	*process;
	int 	checks_amount;

	checks_amount = 0;
	while (data->playing)
	{
		process = data->processes;
		while (process)
		{

			process = process->next;
		}
		data->cycles_fr_lst_check++;
		if (data->cycles_fr_lst_check == data->cycle_to_die)
		{
			check_processes_alive(data);
			checks_amount++;
			if (data->live_op_amount >= NBR_LIVE || checks_amount >= MAX_CHECKS)
			{
				data->cycle_to_die -= CYCLE_DELTA;
				checks_amount = 0;
			}
			data->cycles_fr_lst_check = 0;
			data->live_op_amount = 0;
		}
		data->playing = is_playing(data);
		data->cycle++;
	}
}