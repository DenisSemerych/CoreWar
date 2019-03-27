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

int		time_delay(t_data *data)
{
	return (clock() >= data->vs->time + CLOCKS_PER_SEC / data->vs->delay);
}

void	clear_champs_names(t_list *champs)
{
	char *name;

	while (champs)
	{
		name = ((t_champ*)champs->content)->name;
		while (*name)
		{
			if (ft_isspace(*name))
				*name = ' ';
			name++;
		}
		champs = champs->next;
	}
}

void	draw_winner(t_data *data)
{
	t_list			*winner;
	unsigned int	winner_color;
	char			*winner_name;

	winner = data->champs;
	while (winner &&
		(int)((t_champ*)winner->content)->number != data->last_alive_champ)
		winner = winner->next;
	if (winner)
	{
		winner_color = ((t_champ*)winner->content)->number;
		winner_name = ((t_champ*)winner->content)->name;
		wattron(data->vs->info, COLOR_PAIR(winner_color) | A_BOLD);
		mvwprintw(data->vs->info, IDENT + 25,
			IDENT, "Winner is: %s", winner_name);
		wattroff(data->vs->info, COLOR_PAIR(winner_color) | A_BOLD);
	}
	else
	{
		wattron(data->vs->info, COLOR_PAIR(RED_LIVE) | A_BOLD);
		mvwprintw(data->vs->info, IDENT + 25, IDENT, "NO WINNER!!!");
		wattron(data->vs->info, COLOR_PAIR(RED_LIVE) | A_BOLD);
	}
	wrefresh(data->vs->info);
}

void	visualize(t_data *data)
{
	setlocale(LC_ALL, "");
	create_vs(data);
	clear_champs_names(data->champs);
	while ((data->vs->ch = getch()) != KEY_Q)
	{
		process_keys(data, data->vs->ch);
		if (data->playing && data->vs->ch == KEY_RIGHT)
			do_turn(data);
		else if (data->playing && !data->vs->stop && time_delay(data))
		{
			do_turn(data);
			data->vs->time = clock();
		}
		if (data->playing)
			draw(data);
		else
			draw_winner(data);
	}
	delwin(data->vs->board);
	delwin(data->vs->info);
	delwin(data->vs->usage);
	endwin();
}
