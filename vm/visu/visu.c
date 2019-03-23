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

void	process_keys(t_data *data, int ch)
{
	if (ch == SPACE)
		data->vs->stop = !data->vs->stop;
	else if (ch == KEY_DOWN && data->vs->delay > 10)
		data->vs->delay -= 10;
	else if (ch == KEY_UP)
		data->vs->delay += 10;
}

int		time_delay(t_data *data)
{
	return (clock() >= data->vs->time + CLOCKS_PER_SEC / data->vs->delay);
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
	create_vs(data);
	while ((data->vs->ch = getch()) != KEY_Q)
	{
		process_keys(data, data->vs->ch);
		if (data->vs->ch == KEY_RIGHT && data->playing)
			do_turn(data);
		else if (!data->vs->stop && data->playing && time_delay(data))
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
