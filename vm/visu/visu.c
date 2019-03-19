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
	init_pair(RED, COLOR_RED, COLOR_BLACK);
	init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
	// init_pair(RED_BG, COLOR_BLACK, COLOR_RED);
	// init_pair(GREEN_BG, COLOR_BLACK, COLOR_GREEN);
	// init_pair(YELLOW_BG, COLOR_BLACK, COLOR_YELLOW);
	// init_pair(BLUE_BG, COLOR_BLACK, COLOR_BLUE);
}

/*Make owners map to recognize whose byte is on the current position of the map*/
void	make_owners_map(t_data *data, unsigned char *owners, t_list *champs)
{
	int i;
	int	breakpoint;
	int size;
	int num;

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
		owners[i] = (size-- >= 0) ? num : 0;
	}
}

void	init_visu(t_data *data, t_vs *vs)
{
	initscr();
	keypad(stdscr, true);
	// nodelay(stdscr, true);
	cbreak();
	noecho();
	curs_set(false);
	init_colors();
	// make_owners_map(data, data->owners, data->champs);
	vs->board = create_newwin(HEIGTH, WIDTH, IDENT, IDENT);
	vs->info = create_newwin(HEIGTH / 4 * 3, 60, IDENT, WIDTH + IDENT);
	vs->usage = create_newwin(HEIGTH / 4, 60, HEIGTH - HEIGTH / 4 + IDENT, WIDTH + IDENT);
}

void	run_cycle(void)
{

}

void	visualize(t_data *data)
{
	setlocale(LC_ALL, "");
	data->vs = create_vs(data);
	init_visu(data, data->vs);
	while ((data->vs->ch = wgetch(data->vs->board) != KEY_Q))
	{
		// if (data->vs->ch == SPACE)
		// 	data->vs->stop = !data->vs->stop;
		// if (!data->vs->stop)
		// {
			// run_cycle();
			draw_header(data->vs);
			// draw_board(data->vs);
			draw_usage(data->vs);
		// }
	}
	delwin(data->vs->board);
	delwin(data->vs->info);
	delwin(data->vs->usage);
	endwin();
}
