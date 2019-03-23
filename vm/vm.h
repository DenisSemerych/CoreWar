#ifndef VM_H
# define VM_H

# include "../libft/libft.h"
# include "../includes/op.h"
# include <fcntl.h>

# define DIRECT 0
# define INDIRECT 1

typedef struct		s_process
{
	unsigned int	uniq_number;
	unsigned int	alive_cycle;
	int				parent_number;
	unsigned int	carry: 1;
	unsigned int	live: 1;
	unsigned int	op_code;
	unsigned int	op_args_type[3];
	void			*op_args_pointers[3];
	int				position;
	int				reg[REG_NUMBER + 1];
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
	t_list			*champs;
	int 			champs_amount;
	unsigned int	pl_numbers[MAX_PLAYERS];
	unsigned int	next_p_num;

	int 			dump_flag : 1;
	int 			v_flag : 1;
	int 			n_flag;



	unsigned int	max_process_num;
	int 			last_alive_champ;
	int 			checks_amount;
	unsigned int	playing: 1;
	unsigned char	*board;
	unsigned int	cycle;
	int			 	cycle_to_die;
	unsigned int	cycles_fr_lst_check;
	unsigned int	live_op_amount;

	t_list			*processes;
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
void				introduce_champs(t_list *champs);
void				codage_proc(t_process *process, unsigned char codage);
int 				get_absolute_cord(int cord, int relative_cord);
void				execute_opeartion(t_process *process, t_data *data);
int					write_args_pointers(t_data *data, t_process *process);
int					get_offset(t_process *process);
void				*get_t_ind_pointer(t_data *data, t_process *process, int arg_num);
int 				get_type_size(t_process *process, int arg_type);
void				print_board(const void *addr, size_t size);

#endif
