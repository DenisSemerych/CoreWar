/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inicialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 13:55:02 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/03/15 16:59:11 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	initialization(t_data *data)
{
	unsigned char	*p;
	t_process		new_process;
	t_list			*player_p;

	if (!(data->board = (unsigned char*)ft_memalloc(MEM_SIZE)))
		error_msg("Malloc error while initialization");
	data->cycle_to_die = CYCLE_TO_DIE;
	data->playing = 1;
	p = data->board;
	player_p = data->champs;
	while (player_p)
	{
		ft_bzero(&new_process, sizeof(t_process));
		new_process.uniq_number = ++data->max_process_num;
		new_process.position = p - data->board;
		new_process.live = 1;
		new_process.parent_number = ((t_champ*)player_p->content)->number;
		new_process.reg[1] = ((t_champ*)player_p->content)->number * -1;
		ft_memcpy(p, ((t_champ*)player_p->content)->exec_code,
			((t_champ*)player_p->content)->exec_size);
		ft_lstadd(&data->processes, ft_lstnew(&new_process, sizeof(t_process)));
		p += MEM_SIZE / data->champs_amount;
		player_p = player_p->next;
	}
}
