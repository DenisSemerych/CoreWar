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

unsigned int	get_attributes(t_data *data, t_map *map, int pos)
{
	if ((size_t)data->cycle <= map[pos].cycles_after_live)
		return (COLOR_PAIR(map[pos].owner + 10) | A_BOLD);
	else if (check_process(data, pos))
		return (COLOR_PAIR(map[pos].owner + 5));
	else if ((size_t)data->cycle <= map[pos].cycles_after_st)
		return (COLOR_PAIR(map[pos].owner) | A_BOLD);
	else
		return (COLOR_PAIR(map[pos].owner));
}

void			draw_byte(t_data *data, int pos)
{
	int attr;

	attr = get_attributes(data, data->vs->map, pos);
	wattron(data->vs->board, attr);
	wprintw(data->vs->board, "%02x", data->board[pos]);
	wattroff(data->vs->board, attr);
	waddch(data->vs->board, ' ');
}

void			draw_board(t_data *data, t_vs *vs)
{
	int i;
	int j;

	i = -1;
	wattron(vs->board, A_BOLD);
	mvwprintw(vs->board, 0, WIDTH / 2 - 3, " Arena ");
	wattroff(vs->board, A_BOLD);
	while (++i < BOARD_SIZE)
	{
		j = -1;
		wmove(vs->board, i + 2, j + IDENT + 1);
		while (++j < BOARD_SIZE)
			draw_byte(data, i * BOARD_SIZE + j);
	}
	wrefresh(vs->board);
}
