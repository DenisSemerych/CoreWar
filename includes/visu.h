/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochered <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 10:28:56 by yochered          #+#    #+#             */
/*   Updated: 2019/03/18 10:28:57 by yochered         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

// # include "op.h"
# include <ncurses.h>
# include "libft.h"
# include "../vm/vm.h"
# define RED 1
# define GREEN 2
# define YELLOW 3
# define BLUE 4
# define MAGENTA 5
# define CYAN 6

# define IDENT 3
# define BOARD_SIZE 64
# define HEIGTH (BOARD_SIZE + 4)
# define WIDTH (BOARD_SIZE * 3 + IDENT * 2)

# define ESC 27
# define SPACE ' '

typedef struct	vs
{
	int				ch;
	int 			width;
	int 			heigth;
	unsigned char	stop;
	unsigned int	speed;
	WINDOW			*board;
	WINDOW			*info;
	t_data			*data;
}				t_vs;

void			visualize(t_data *data);
WINDOW			*create_newwin(int height, int width, int y, int x);
void			destroy_win(WINDOW *win);
void			set_border(WINDOW *win);
void			draw_board(t_vs *vs);

#endif
