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

#include "vm.h"

void	initialization(t_data *data)
{
	unsigned char	*p;
	int				pos;	
	t_process		new_carriage;
	t_list			*player_p;

	if (!(data->board = (unsigned char*)malloc(MEM_SIZE)))
		error_msg("Malloc error while initialization");
	ft_bzero(data->board, MEM_SIZE);
	data->cycle_to_die = CYCLE_TO_DIE;
	data->playing = 1;
	pos = MEM_SIZE / data->champs_amount;
	p = data->board;
	player_p = data->champs;
	while (player_p)
	{
		ft_bzero(&new_carriage, sizeof(t_process));
		new_carriage.position = p - data->board;
		new_carriage.live = 1;
		new_carriage.parent_number = ((t_champ*)player_p->content)->number;
		ft_memcpy(p, ((t_champ*)player_p->content)->exec_code, CHAMP_MAX_SIZE);
		ft_lstadd(&data->processes, ft_lstnew(&new_carriage, sizeof(t_process)));
		p += pos;
		player_p = player_p->next;
	}
}