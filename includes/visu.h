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

# include "../vm/vm.h"
# include <ncurses.h>
# include "stdbool.h"
# include "libft.h"
# include "locale.h"
# define WHITE 0
# define RED 1
# define GREEN 2
# define YELLOW 3
# define BLUE 4
# define MAGENTA 5
# define CYAN 6
# define WHITE_BG 7
# define RED_BG 8
# define GREEN_BG 9
# define YELLOW_BG 10
# define BLUE_BG 11

# define IDENT 3
# define BOARD_SIZE 64
# define HEIGTH (BOARD_SIZE + 4)
# define WIDTH (BOARD_SIZE * 3 + IDENT * 2)

# define COR1 L" ██████╗ ██████╗ ██████╗ ███████╗██╗    ██╗ █████╗ ██████╗ "
# define COR2 L"██╔════╝██╔═══██╗██╔══██╗██╔════╝██║    ██║██╔══██╗██╔══██╗"
# define COR3 L"██║     ██║   ██║██████╔╝█████╗  ██║ █╗ ██║███████║██████╔╝"
# define COR4 L"██║     ██║   ██║██╔══██╗██╔══╝  ██║███╗██║██╔══██║██╔══██╗"
# define COR5 L"╚██████╗╚██████╔╝██║  ██║███████╗╚███╔███╔╝██║  ██║██║  ██║"
# define COR6 L" ╚═════╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝ ╚══╝╚══╝ ╚═╝  ╚═╝╚═╝  ╚═╝"

# define SPACE ' '
# define KEY_Q 'q'

typedef struct	s_map
{
	size_t	owner : 1;
	size_t	cycles_after_st : 1;
	size_t	cycles_after_live: 1;
}				t_map;

typedef struct	s_vs
{
	int				ch;
	int				width;
	int				heigth;
	unsigned int	speed;
	bool			stop;
	t_map			*map;
	WINDOW			*board;
	WINDOW			*info;
	WINDOW			*usage;
	struct s_data	*data;
}				t_vs;

void			visualize(struct s_data *data);
WINDOW			*create_newwin(int height, int width, int y, int x);
void			destroy_win(WINDOW *win);
void			set_border(WINDOW *win);
void			draw_board(struct s_data *data, t_vs *vs);
void			draw_usage(t_vs *vs);
void			draw_info(struct s_data *data);
void			draw_header(t_vs *vs);

#endif
