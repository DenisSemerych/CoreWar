/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochered <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 14:02:26 by yochered          #+#    #+#             */
/*   Updated: 2019/03/23 14:02:27 by yochered         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_map	*make_map(t_data *data, t_list *champs)
{
	int		i;
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

void	create_vs(t_data *data)
{
	float	info_width;

	if (!(data->vs = (t_vs*)ft_memalloc(sizeof(t_vs))))
		exit(1);
	data->vs->data = data;
	data->vs->stop = true;
	data->vs->delay = 50;
	initscr();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	curs_set(false);
	cbreak();
	noecho();
	init_colors();
	getmaxyx(stdscr, data->vs->heigth, data->vs->width);
	data->vs->map = make_map(data, data->champs);
	info_width = (float)data->vs->width / 100 * 25 - IDENT * 2;
	data->vs->board = create_newwin(HEIGTH, WIDTH, IDENT,  (data->vs->width -
	WIDTH - info_width - 9) / 2);
	data->vs->usage = create_newwin(HEIGTH / 4, info_width,
			HEIGTH - HEIGTH / 4 + IDENT, (data->vs->width - WIDTH - info_width
			- 9)	/ 2 + WIDTH + 9);
	data->vs->info = create_newwin(HEIGTH / 4 * 3 - IDENT,
		info_width, IDENT, (data->vs->width - WIDTH - info_width - 9) / 2 +
		WIDTH + 9);
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
	init_pair(WHITE_LIVE, COLOR_WHITE, COLOR_CYAN);
	init_pair(RED_LIVE, COLOR_WHITE, COLOR_RED);
	init_pair(GREEN_LIVE, COLOR_WHITE, COLOR_GREEN);
	init_pair(YELLOW_LIVE, COLOR_WHITE, COLOR_YELLOW);
	init_pair(CYAN_LIVE, COLOR_WHITE, COLOR_CYAN);
}
