/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochered <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 15:02:00 by yochered          #+#    #+#             */
/*   Updated: 2019/03/18 15:02:02 by yochered         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	set_border(WINDOW *win)
{
	wattron(win, COLOR_PAIR(CYAN));
	box(win, 0, 0);
	wattroff(win, COLOR_PAIR(CYAN));
}

WINDOW	*create_newwin(int height, int width, int y, int x)
{
	WINDOW *win;

	win = newwin(height, width, y, x);
	wrefresh(win);
	return (win);
}

void	destroy_win(WINDOW *win)
{
	wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(win);
	delwin(win);
}
