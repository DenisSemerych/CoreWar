
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

#include "vm.h"

t_vs	*create_vs(t_data *data)
{
	t_vs *vs;

	if (!(vs = (t_vs*)ft_memalloc(sizeof(t_vs))))
		exit(1);
	vs->stop = true;
	vs->data = data;
	vs->delay = 50;
	return (vs);
}

void	init_colors(void)
{
	start_color();
	init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
	init_pair(RED, COLOR_RED, COLOR_BLACK);
	init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
	init_pair(WHITE_BG, COLOR_BLACK, COLOR_WHITE);
	init_pair(RED_BG, COLOR_BLACK, COLOR_RED);
	init_pair(GREEN_BG, COLOR_BLACK, COLOR_GREEN);
	init_pair(YELLOW_BG, COLOR_BLACK, COLOR_YELLOW);
	init_pair(CYAN_BG, COLOR_BLACK, COLOR_CYAN);
}

/*Make map to recognize byte's type on the current position of the map*/
t_map	*make_map(t_data *data, t_list *champs)
{
	int 	i;
	int		breakpoint;
	int		size;
	size_t	num;
	t_map	*map;

	map = (t_map*)ft_memalloc(sizeof(t_map) * MEM_SIZE);
	breakpoint = MEM_SIZE / data->champs_amount;
	i = -1;
	while (++i < MEM_SIZE)
	{
		if (champs && i % breakpoint == 0)
		{
			size = ((t_champ*)champs->content)->exec_size;
			num = ((t_champ*)champs->content)->number;
			champs = champs->next;
		}
		if (size-- >= 0)
			map[i].owner = num;
	}
	return (map);
}

void	init_visu(t_data *data, t_vs *vs)
{
	float info_width;

	initscr();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	curs_set(false);
	cbreak();
	noecho();
	init_colors();
	getmaxyx(stdscr, vs->heigth, vs->width);
	data->vs->map = make_map(data, data->champs);
	info_width = (float)vs->width / 100 * 30 - IDENT * 2;
	vs->board = create_newwin(HEIGTH, WIDTH, IDENT, IDENT);
	vs->usage = create_newwin(HEIGTH / 4, info_width, HEIGTH - HEIGTH / 4 + IDENT, vs->width - info_width - IDENT);
	vs->info = create_newwin(HEIGTH / 4 * 3 - IDENT, info_width, IDENT, vs->width - info_width - IDENT);
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

void	visualize(t_data *data)
{
	setlocale(LC_ALL, "");
	data->vs = create_vs(data);
	init_visu(data, data->vs);
	while ((data->vs->ch = getch()) != KEY_Q)
	{
		process_keys(data, data->vs->ch);
		if (data->vs->ch == KEY_RIGHT && data->playing)
			do_turn(data);
		else if (!data->vs->stop && data->playing && clock() >= data->vs->time + CLOCKS_PER_SEC / data->vs->delay)
		{
			do_turn(data);
			data->vs->time = clock();
		}
		draw(data);
	}
	delwin(data->vs->board);
	delwin(data->vs->info);
	delwin(data->vs->usage);
	endwin();
}
