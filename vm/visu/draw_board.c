/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_board.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochered <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 15:39:43 by yochered          #+#    #+#             */
/*   Updated: 2019/03/18 15:39:44 by yochered         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				check_process(t_data *data, int index)
{
	t_list *process;

	process = data->processes;
	while (process)
	{
		if (((t_process*)process->content)->position == index)
			return (1);
		process = process->next;
	}
	return (0);
}

/*Sets attributes to recognize player's color and carry color*/
unsigned int	get_attributes(t_data *data, t_map *map, int pos)
{
	if (map[pos].cycles_after_st > 0)
		map[pos].cycles_after_st--;
	else if (map[pos].cycles_after_live > 0)
		map[pos].cycles_after_live--;
	if (map[pos].cycles_after_live > 0)
		return (COLOR_PAIR(map[pos].owner + 7) | A_BOLD);
	else if (map[pos].owner && check_process(data, pos))
		return (COLOR_PAIR(map[pos].owner + 7));	//Current color background
	else if (map[pos].cycles_after_st > 0)
		return (COLOR_PAIR(map[pos].owner | A_BOLD));
	else
		return (COLOR_PAIR(map[pos].owner));
}

void			draw_board(t_data *data, t_vs *vs)
{
	int i;
	int j;
	int attr;

	i = -1;
	wattron(vs->board, A_BOLD);
	mvwprintw(vs->board, 0, WIDTH / 2 - 3, " Arena ");
	wattroff(vs->board, A_BOLD);
	while (++i < BOARD_SIZE)
	{
		j = -1;
		wmove(vs->board, i + 2, j + IDENT + 1);
		while (++j < BOARD_SIZE)
		{
			attr = get_attributes(data, data->vs->map, i * 64 + j);
			wattron(vs->board, attr);
			wprintw(vs->board, "%2x", data->board[i * BOARD_SIZE + j]);
			wattroff(vs->board, attr);
			waddch(vs->board, ' ');
		}
	}
	wrefresh(vs->board);
}
