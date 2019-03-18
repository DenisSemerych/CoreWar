/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_board.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochered <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 15:39:43 by yochered          #+#    #+#             */
/*   Updated: 2019/03/18 15:39:44 by yochered         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	draw_board(t_vs *vs)
{
	int i;
	int j;

	i = -1;
	while (++i < BOARD_SIZE)
	{
		j = -1;
		wmove(vs->board, i + 2, j + IDENT + 1);
		while (++j < BOARD_SIZE)
		{
			wprintw(vs->board, "%-3.2x", 255);
		}
	}
	wrefresh(vs->board);
}
