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
	wattron(vs->info, A_BOLD);
	mvwprintw(vs->info, 0, 30 - 9, " Game Information ");
	wattroff(vs->info, A_BOLD);
	wattron(vs->info, COLOR_PAIR(RED));
	mvwprintw(vs->info, IDENT, IDENT, "%ls", L" _____  _____ ______  _____  _    _   ___  ______");
	mvwprintw(vs->info, IDENT + 1, IDENT, "%ls", L"/  __ \\|  _  || ___ \\|  ___|| |  | | / _ \\ | ___ \\");
	mvwprintw(vs->info, IDENT + 2, IDENT, "%ls", L"| /  \\/| | | || |_/ /| |__  | |  | |/ /_\\ \\| |_/ /");
	mvwprintw(vs->info, IDENT + 3, IDENT, "%ls", L"| |    | | | ||    / |  __| | |/\\| ||  _  ||    /");
	mvwprintw(vs->info, IDENT + 4, IDENT, "%ls", L"| |    | | | ||    / |  __| | |/\\| ||  _  ||    /");
	mvwprintw(vs->info, IDENT + 5, IDENT, "%ls", L"| \\__/\\\\ \\_/ /| |\\ \\ | |___ \\  /\\  /| | | || |\\ \\");
	mvwprintw(vs->info, IDENT + 6, IDENT, "%ls", L" \\____/ \\___/ \\_| \\_|\\____/  \\/  \\/ \\_| |_/\\_| \\_|");
	wattroff(vs->info, COLOR_PAIR(RED));
	wrefresh(vs->info);
}

void	draw_usage(t_vs *vs)
{
	int i;

	i = 2;
	wattron(vs->usage, A_BOLD);
	mvwprintw(vs->usage, 0, 30 - 4, " Usage ");
	wattron(vs->usage, COLOR_PAIR(CYAN));
	mvwprintw(vs->usage, i, IDENT, "%-15s%15s", "Speed up:", "[Arrow up]");
	mvwprintw(vs->usage, ++i, IDENT, "%-15s%15s", "Speed down:", "[Arrow down]");
	mvwprintw(vs->usage, ++i, IDENT, "%-15s%15s", "Pause:", "[Space]");
	mvwprintw(vs->usage, ++i, IDENT, "%-15s%15s", "Quit:", "[Q]");
	wattroff(vs->usage, COLOR_PAIR(CYAN));
	wrefresh(vs->usage);
}
