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

typedef struct		s_carriage
{
	int				position;
	int				carry_flag;
	int				live_flag;
	int				parent_number;
	unsigned int	reg[16];
	int				current_command;
	int				cycles_to_go;
}					t_carriage;


void	inicialization(t_list *players, t_list **carriages, unsigned char *mem_board)
{
	unsigned char	*p;
	int				pos;	
	t_carriage		new_carriage;

	if (!(mem_board = (unsigned char*)malloc(MEM_SIZE)))
		error_msg("Malloc error while initialization");
	ft_bzero(mem_board, MEM_SIZE);
	pos = MEM_SIZE / ft_lstcount(players);
	p = mem_board;
	while (players)
	{
		ft_bzero(&new_carriage, sizeof(t_carriage));
		new_carriage.position = p - mem_board;
		new_carriage.live_flag = 1;
		new_carriage.parent_number = ((t_champ*)players->content)->number;
		ft_memcpy(p, ((t_champ*)players->content)->exec_code, CHAMP_MAX_SIZE);
		ft_lstadd(carriages, ft_lstnew(&new_carriage, sizeof(new_carriage)));
		p += pos;
		players = players->next;
	}
}

void	play()
{






}

void	turn()
{




}
