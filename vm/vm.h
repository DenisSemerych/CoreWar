#ifndef VM_H
# define VM_H

# include "../libft/libft.h"
# include "../includes/op.h"
# include <fcntl.h>

typedef struct		s_process
{
	unsigned int	uniq_number;
	unsigned int	alive_cycle;
	int				parent_number;
	unsigned int	carry: 1;
	unsigned int	live: 1;
	unsigned int	op_code;
	int				position;
	unsigned int	reg[REG_NUMBER];
	int				current_command;
	int				waiting_cycles;
}					t_process;

typedef struct 		s_champ
{
	unsigned int	number;
	char			*name;
	char			*comment;
	unsigned int	exec_size;
	unsigned int	magic_header;
	unsigned char	*exec_code;
}					t_champ;

typedef struct 		s_data
{
	unsigned int	playing: 1;
	unsigned char	*board;
	unsigned int	pl_numbers[MAX_PLAYERS];
	unsigned int	next_p_num;
	unsigned int	cycle;
	unsigned int	last_check_cycle;
	t_list			*champs;
	t_list			*processes;
	int 			champs_amount;
	int 			dump_flag;
	int 			cycle_to_die;
}					t_data;

void				error_msg(char *str);
int					parse_int(char *str);
char 				*get_champ_name(int fd);
char				*get_champ_comment(int fd);
unsigned int		get_champ_4_bytes(int fd);
void				print_champ(t_champ * champ, int pr_memory);
unsigned char		*get_champ_exec(int fd, int code_size);
void				arg_valid(int argc, char** argv, t_data *data);
void				reserve_numbers(int argc, char **argv, t_data *data);
void				print_data(t_data *data);
void				initialization(t_data *data);
void				do_turn(t_data *data);
//void				introduce_champs(t_list *champs);

#endif
