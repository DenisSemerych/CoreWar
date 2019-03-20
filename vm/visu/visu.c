
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
	return (vs);
}

void	init_colors(void)
{
	start_color();
	init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
	init_pair(RED, COLOR_RED, COLOR_BLACK);
	init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
	init_pair(WHITE_BG, COLOR_BLACK, COLOR_WHITE);
	init_pair(RED_BG, COLOR_BLACK, COLOR_RED);
	init_pair(GREEN_BG, COLOR_BLACK, COLOR_GREEN);
	init_pair(YELLOW_BG, COLOR_BLACK, COLOR_YELLOW);
	init_pair(BLUE_BG, COLOR_BLACK, COLOR_BLUE);
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
	data->champs_amount = 2;//Champs amount must not to be zero
	breakpoint = MEM_SIZE / data->champs_amount;
	i = -1;
	while (++i < MEM_SIZE)
	{
		if (i % breakpoint == 0)
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
	float board_width;
	float info_width;

	initscr();
	keypad(stdscr, true);
	// nodelay(stdscr, true);
	cbreak();
	noecho();
	curs_set(false);
	init_colors();
	// data->vs->map = make_map(data, data->champs);
	getmaxyx(stdscr, vs->heigth, vs->width);
	board_width = (float)vs->width / 100 * 70 - IDENT * 2;
	info_width = (float)vs->width / 100 * 30 - IDENT * 2;
	printf("%f %d\n", board_width, vs->width);
	vs->board = create_newwin(HEIGTH, board_width, IDENT, IDENT);
	vs->info = create_newwin(HEIGTH / 4 * 3 - IDENT, info_width, IDENT, vs->width - info_width - IDENT);
	vs->usage = create_newwin(HEIGTH / 4, info_width, HEIGTH - HEIGTH / 4 + IDENT, vs->width - info_width - IDENT);
}

// void	run_cycle(void)
// {
// 	read_operations(data);
// 	execute_operations(data);/*Function like do_turn(), but with visualizer's options*/
// 	if (data->cycles_fr_lst_check >= data->cycle_to_die)
// 		to_die_check(data);
// 	is_playing_check(data);
// 	data->cycles_fr_lst_check++;
// 	data->cycle++;
// }

void	process_keys(t_data *data, int ch)
{
	if (ch == SPACE)
		data->vs->stop = !data->vs->stop;
	else if (ch == KEY_UP)
		data->vs->speed += 10;
	else if (ch == KEY_DOWN)
		data->vs->speed -= 10;
}

void	visualize(t_data *data)
{
	setlocale(LC_ALL, "");
	data->vs = create_vs(data);
	init_visu(data, data->vs);
	while ((data->vs->ch = wgetch(data->vs->board) != KEY_Q))
	{
		process_keys(data, data->vs->ch);
		// if (!data->vs->stop)
		// {
			// run_cycle();
			draw_info(data);
			// draw_board(data, data->vs);
			draw_usage(data->vs);
		// }
	}
	delwin(data->vs->board);
	delwin(data->vs->info);
	delwin(data->vs->usage);
	endwin();
}
