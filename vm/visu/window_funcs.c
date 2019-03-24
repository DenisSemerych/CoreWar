/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochered <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 15:02:00 by yochered          #+#    #+#             */
/*   Updated: 2019/03/18 15:02:02 by yochered         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	draw_header(t_vs *vs)
{
	int x;
	int y;

	getmaxyx(vs->info, y, x);
	wattron(vs->info, A_BOLD);
	mvwprintw(vs->info, 0, x / 2 - 9, " Game Information ");
	wattroff(vs->info, A_BOLD);
	wattron(vs->info, COLOR_PAIR(CYAN));
	mvwprintw(vs->info, IDENT, IDENT, "%ls", COR1);
	mvwprintw(vs->info, IDENT + 1, IDENT, "%ls", COR2);
	mvwprintw(vs->info, IDENT + 2, IDENT, "%ls", COR3);
	mvwprintw(vs->info, IDENT + 3, IDENT, "%ls", COR4);
	mvwprintw(vs->info, IDENT + 4, IDENT, "%ls", COR5);
	mvwprintw(vs->info, IDENT + 5, IDENT, "%ls", COR6);
	wattroff(vs->info, COLOR_PAIR(CYAN));
}

void	set_border(WINDOW *win)
{
	wattron(win, COLOR_PAIR(CYAN));
	box(win, 0, 0);
	wattroff(win, COLOR_PAIR(CYAN));
}

WINDOW	*create_newwin(int height, int width, int y, int x)
{
	WINDOW *win;

	win = newwin(height, width, y, x);
	wrefresh(win);
	return (win);
}

void	process_keys(t_data *data, int ch)
{
	if (ch == SPACE)
		data->vs->stop = !data->vs->stop;
	else if (ch == KEY_DOWN && data->vs->delay > 10)
		data->vs->delay -= 10;
	else if (ch == KEY_UP)
		data->vs->delay += 10;
}

void	draw(t_data *data)
{
	werase(data->vs->info);
	werase(data->vs->usage);
	werase(data->vs->board);
	set_border(data->vs->info);
	set_border(data->vs->usage);
	set_border(data->vs->board);
	draw_info(data);
	draw_usage(data->vs);
	draw_board(data, data->vs);
	wrefresh(data->vs->info);
	wrefresh(data->vs->usage);
	wrefresh(data->vs->board);
}
