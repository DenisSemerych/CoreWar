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
# include "stdbool.h"
# include "libft.h"
# include "locale.h"
# define RED 1
# define GREEN 2
# define YELLOW 3
# define BLUE 4
# define MAGENTA 5
# define CYAN 6
# define RED_BG 7
# define GREEN_BG 8
# define YELLOW_BG 9
# define BLUE_BG 10

# define IDENT 3
# define BOARD_SIZE 64
# define HEIGTH (BOARD_SIZE + 4)
# define WIDTH (BOARD_SIZE * 3 + IDENT * 2)

// # define COR1 L" ▓▓▓▓    ▓▓▓   ▓▓▓▓   ▌  ▓  ▐   ▓      ▓▓▓▓"
// # define COR2 L"▓▓   ▓  ▓   ▓  ▓  ▓▓  ▌  ▓  ▐  ▓  ▓    ▓  ▓▓"
// # define COR3 L"▓▓      ▓   ▓  ▓▓▓▓   ▌  ▓  ▐  ▓▃▃▃▃▓  ▓▓▓▓"
// # define COR4 L" ▓▓  ▓  ▓   ▓  ▓   ▓   ▙ ▓ ▟   ▓     ▓s ▓   ▓"
// # define COR5 L"  ▓▓▓▓   ▓▓▓   ▓    ▓    ▓     ▓     ▓s ▓    ▓"

# define COR1 L" _____  _____ ______  _____  _    _   ___  ______ "
# define COR2 L"/  __ \\|  _  || ___ \\|  ___|| |  | | / _ \\ | ___ \\"
# define COR3 L"| /  \\/| | | || |_/ /| |__  | |  | |/ /_\\ \\| |_/ /"
# define COR4 L"| |   | | | |    /|  __|| |/\\\\| |  _  ||    /"
# define COR5 L"| |    | | | ||    / |  __| | |/\\| ||  _  ||    /"
# define COR6 L"| \\__/\\\\ \\_/ /| |\\ \\ | |___ \\  /\\  /| | | || |\\ \\"
# define COR7 L" \\____/ \\___/ \\_| \\_|\\____/  \\/  \\/ \\_| |_/\\_| \\_|"

# define SPACE ' '
# define KEY_Q 'q'

typedef struct	s_vs
{
	int				ch;
	int 			width;
	int 			heigth;
	unsigned int	speed;
	WINDOW			*board;
	WINDOW			*info;
	WINDOW			*usage;
	bool			stop;
	struct s_data	*data;
}				t_vs;

void				visualize(struct s_data *data);
WINDOW				*create_newwin(int height, int width, int y, int x);
void				destroy_win(WINDOW *win);
void				set_border(WINDOW *win);
void				draw_board(struct s_data *data, t_vs *vs);
void				draw_usage(t_vs *vs);
void				draw_header(t_vs *vs);

#endif
