/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochered <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 10:31:45 by yochered          #+#    #+#             */
/*   Updated: 2019/03/18 10:31:46 by yochered         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

t_vs	*create_vs(t_data *data)
{
	t_vs *vs;

	if (!(vs = (t_vs*)ft_memalloc(sizeof(t_vs))))
		exit(1);
	vs->stop = true;
	vs->data = data;
	return (vs);
}

void	set_colors(void)
{
	start_color();
	init_pair(RED, COLOR_RED, COLOR_BLACK);
	init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
}

void	init_visu(t_vs *vs)
{
	initscr();
	keypad(stdscr, true);
	// nodelay(stdscr, true);
	cbreak();
	noecho();
	curs_set(false);
	set_colors();
	vs->board = create_newwin(HEIGTH, WIDTH, IDENT, IDENT);
	vs->info = create_newwin(HEIGTH, 100, IDENT, WIDTH + IDENT);
}

void	visualize(t_data *data)
{
	t_vs	*vs;

	vs = create_vs(data);
	init_visu(vs);
	draw_board(vs);
	usleep(5000000);
	endwin();
}
