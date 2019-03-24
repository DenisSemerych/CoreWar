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
		mvwprintw(data->vs->info, IDENT + 9 + i, IDENT, "%d. %s", i, name);
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
	mvwprintw(vs->usage, ++i, IDENT, "%-15s%15s", "Pause:", "[Space]");
	mvwprintw(vs->usage, ++i, IDENT, "%-15s%15s", "Quit:", "[Q]");
	wattroff(vs->usage, COLOR_PAIR(CYAN));
}

void	draw_stat(t_data *data)
{
	wattron(data->vs->info, A_BOLD);
	if (data->vs->stop)
		mvwprintw(data->vs->info, IDENT + 8, IDENT, "STOPPED");
	else
		mvwprintw(data->vs->info, IDENT + 8, IDENT, "RUNNING");
	wattroff(data->vs->info, A_BOLD);
	mvwprintw(data->vs->info, IDENT + 15, IDENT,
			"%-15s%d", "Speed:", data->vs->delay);
	mvwprintw(data->vs->info, IDENT + 16, IDENT,
			"%-15s%d", "Cycle:", data->cycle);
	mvwprintw(data->vs->info, IDENT + 17, IDENT,
			"%-15s%d", "Cycle delta:", CYCLE_DELTA);
	mvwprintw(data->vs->info, IDENT + 18, IDENT,
			"%-15s%d", "Cycle to die:", data->cycle_to_die);
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
		mvwprintw(vs->info, IDENT + 15 + ++i, IDENT,
				"#%d %d", ptr->uniq_number, ptr->current_command);
		wattroff(vs->info, COLOR_PAIR(vs->map[ptr->position].owner));
		processes = processes->next;
	}
}

void	draw_info(t_data *data)
{
	draw_header(data->vs);
	draw_champs(data);
	draw_stat(data);
}
