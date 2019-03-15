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
		if (((t_process*)process->content)->live)
			return (1);
		process = process->next;
	}
	return (0);
}

void	check_process_alive(t_data *data)
{
	t_list	*process;

	process = data->processes;
	while (process)
	{
		if (!((t_process*)process->content)->live)
			continue;
		if (((t_process*)process->content)->alive_cycle - data->cycle_to_die > 0)
			((t_process*)process->content)->live = 0;
		process = process->next;
	}
}

void	do_turn(t_data *data)
{




	if (data->cycle - data->last_check_cycle == data->cycle_to_die)
		check_process_alive(data);
	data->playing = is_playing(data);
	data->cycle++;
}