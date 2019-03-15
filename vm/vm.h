#ifndef VM_H
# define VM_H

# include "../libft/libft.h"
# include "../includes/op.h"
# include <fcntl.h>

/*typedef struct		s_process
{
	unsigned int	uniq_number;
	unsigned int	carry : 1;
	unsigned int	op_code;
}					t_process; */

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
	unsigned int	pl_numbers[MAX_PLAYERS];
	unsigned int	next_p_num;
	t_list			*champs;
	int 			champs_amount;
	int 			dump_flag;
}					t_data;

void	error_msg(char *str);
int		parse_int(char *str);

char	*get_champ_name(int fd);
char	*get_champ_comment(int fd);
//char	*get_champ_code(int fd);
unsigned int	*get_champ_4_bytes(int fd);
void	print_champ(t_champ * champ, int pr_memory);
unsigned char	*get_champ_exec(int fd, int code_size);
void			arg_valid(int argc, char** argv, t_data *data);
void			reserve_numbers(int argc, char **argv, t_data *data);
void			print_data(t_data *data);

#endif
