/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochered <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 10:10:51 by yochered          #+#    #+#             */
/*   Updated: 2019/03/19 10:10:52 by yochered         ###   ########.fr       */
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
	wrefresh(vs->info);
}

void	draw_usage(t_vs *vs)
{
	int i;
	int x;
	int y;

	i = 2;
	getmaxyx(vs->usage, y, x);
	wattron(vs->usage, A_BOLD);
	mvwprintw(vs->usage, 0, x / 2 - 4, " Usage ");
	wattron(vs->usage, COLOR_PAIR(CYAN));
	mvwprintw(vs->usage, i, IDENT, "%-15s%15s", "Speed up:", "[Arrow up]");
	mvwprintw(vs->usage, ++i, IDENT, "%-15s%15s", "Speed down:", "[Arrow down]");
	mvwprintw(vs->usage, ++i, IDENT, "%-15s%15s", "Pause:", "[Space]");
	mvwprintw(vs->usage, ++i, IDENT, "%-15s%15s", "Quit:", "[Q]");
	wattroff(vs->usage, COLOR_PAIR(CYAN));
	wrefresh(vs->usage);
}

void	draw_stat(t_data *data)
{
	mvwprintw(data->vs->info, IDENT + 8, IDENT, "%-15s%d", "Cycle:", data->cycle);
	mvwprintw(data->vs->info, IDENT + 9, IDENT, "%-15s%d", "Cycle delta:", CYCLE_DELTA);
	mvwprintw(data->vs->info, IDENT + 10, IDENT, "%-15s%d", "Cycle to die:", data->cycle_to_die);
	wrefresh(data->vs->info);
}

void	draw_processes(t_vs *vs, t_list *processes)
{
	int			i;
	t_process	*ptr;

	i = -1;
	while (processes)
	{
		ptr = (t_process*)processes->content;
		wattron(vs->info, COLOR_PAIR(vs->map[ptr->position].owner));
		mvwprintw(vs->info, IDENT + 15 + ++i, IDENT, "#%d %d", ptr->uniq_number, ptr->current_command);
		wattroff(vs->info, COLOR_PAIR(vs->map[ptr->position].owner));
		processes = processes->next;
	}
}

void	draw_info(t_data *data)
{
	draw_header(data->vs);
	draw_stat(data);
}
