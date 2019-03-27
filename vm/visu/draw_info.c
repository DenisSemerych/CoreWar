/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochered <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 10:10:51 by yochered          #+#    #+#             */
/*   Updated: 2019/03/27 15:51:55 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	draw_champs(t_data *data)
{
	t_list	*champ;
	char	*name;
	int		color;
	int		i;

	i = 0;
	champ = data->champs;
	while (champ)
	{
		i++;
		name = ((t_champ*)champ->content)->name;
		color = ((t_champ*)champ->content)->number;
		wattron(data->vs->info, COLOR_PAIR(color) | A_BOLD);
		mvwprintw(data->vs->info, IDENT + 12 + i, IDENT, "%d. %s", i, name);
		wattroff(data->vs->info, COLOR_PAIR(color) | A_BOLD);
		champ = champ->next;
	}
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
	mvwprintw(vs->usage, ++i, IDENT, "%-15s%15s",
			"Speed down:", "[Arrow down]");
	mvwprintw(vs->usage, ++i, IDENT, "%-15s%15s", "Next turn:",
			"[Right arrow]");
	mvwprintw(vs->usage, ++i, IDENT, "%-15s%15s", "Pause:", "[Space]");
	mvwprintw(vs->usage, ++i, IDENT, "%-15s%15s", "Quit:", "[Q]");
	mvwprintw(vs->usage, ++i, IDENT, "%-15s%8s", "Change zero byte mode:",
			"[C]");
	wattroff(vs->usage, COLOR_PAIR(CYAN));
}

void	draw_stat(t_data *d)
{
	wattron(d->vs->info, COLOR_PAIR(CYAN));
	if (d->vs->stop)
	{
		mvwprintw(d->vs->info, IDENT + 7, d->vs->width / 8 - 19, "%ls", PAUS1);
		mvwprintw(d->vs->info, IDENT + 8, d->vs->width / 8 - 19, "%ls", PAUS2);
		mvwprintw(d->vs->info, IDENT + 9, d->vs->width / 8 - 19, "%ls", PAUS3);
		mvwprintw(d->vs->info, IDENT + 10, d->vs->width / 8 - 19, "%ls", PAUS4);
		mvwprintw(d->vs->info, IDENT + 11, d->vs->width / 8 - 19, "%ls", PAUS5);
	}
	else
	{
		mvwprintw(d->vs->info, IDENT + 7, d->vs->width / 8 - 24, "%ls", RUN1);
		mvwprintw(d->vs->info, IDENT + 8, d->vs->width / 8 - 24, "%ls", RUN2);
		mvwprintw(d->vs->info, IDENT + 9, d->vs->width / 8 - 24, "%ls", RUN3);
		mvwprintw(d->vs->info, IDENT + 10, d->vs->width / 8 - 24, "%ls", RUN4);
		mvwprintw(d->vs->info, IDENT + 11, d->vs->width / 8 - 24, "%ls", RUN5);
	}
	wattroff(d->vs->info, COLOR_PAIR(CYAN));
	mvwprintw(d->vs->info, IDENT + 18, IDENT,
			"%-15s%d", "Speed:", d->vs->delay);
	mvwprintw(d->vs->info, IDENT + 19, IDENT, "%-15s%d", "Cycle:", d->cycle);
	mvwprintw(d->vs->info, IDENT + 20, IDENT,
			"%-15s%d", "Cycle delta:", CYCLE_DELTA);
	mvwprintw(d->vs->info, IDENT + 21, IDENT,
			"%-15s%d", "Cycle to die:", d->cycle_to_die);
}

void	draw_info(t_data *data)
{
	draw_header(data->vs);
	draw_champs(data);
	draw_stat(data);
}
