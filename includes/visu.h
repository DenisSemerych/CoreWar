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
# include "time.h"

# define WHITE 0
# define RED 1
# define GREEN 2
# define YELLOW 3
# define CYAN 4

# define WHITE_BG 5
# define RED_BG 6
# define GREEN_BG 7
# define YELLOW_BG 8
# define CYAN_BG 9

# define WHITE_LIVE 10
# define RED_LIVE 11
# define GREEN_LIVE 12
# define YELLOW_LIVE 13
# define CYAN_LIVE 14

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
	size_t	owner;
	size_t	cycles_after_st;
	size_t	cycles_after_live;
}				t_map;

typedef struct	s_vs
{
	int				ch;
	int				width;
	int				heigth;
	unsigned int	delay;
	clock_t			time;
	bool			stop;
	t_map			*map;
	WINDOW			*board;
	WINDOW			*info;
	WINDOW			*usage;
	struct s_data	*data;
}				t_vs;

void			visualize(struct s_data *data);
void			create_vs(struct s_data *data);
void			init_colors(void);
WINDOW			*create_newwin(int height, int width, int y, int x);
void			destroy_win(WINDOW *win);
void			set_border(WINDOW *win);
void			draw_board(struct s_data *data, t_vs *vs);
void			draw_usage(t_vs *vs);
void			draw_info(struct s_data *data);
void			draw_header(t_vs *vs);
t_map			*make_map(struct s_data *data, t_list *champs);

#endif
