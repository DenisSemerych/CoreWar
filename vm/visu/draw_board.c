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
unsigned int	get_attributes(t_data *data, int i, int j)
{
	if (data->owners[i * 64 + j] && check_process(data, i * 64 + j))
		return (COLOR_PAIR(data->owners[i * 64 + j] + 6));	//Current color background
	else if (data->owners[i * 64 + j])
		return (COLOR_PAIR(data->owners[i * 64 + j]));
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
			attr = get_attributes(data, i, j);
			wattron(vs->board, attr);
			wprintw(vs->board, "%2x", data->board[i * BOARD_SIZE + j]);
			wattroff(vs->board, attr);
			waddch(vs->board, ' ');
		}
	}
	wrefresh(vs->board);
}
