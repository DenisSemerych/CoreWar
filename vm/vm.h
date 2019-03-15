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
	size_t 			size;
	//unsigned int	*code;
}					t_champ;

typedef struct 		s_data
{
	unsigned int	pl_numbers[MAX_PLAYERS];
	unsigned int	next_p_num;
	t_list			*champs;
	int 			champs_amount;
}					t_data;

void	error_msg(char *str);
int		parse_int(char *str);

char	*get_champ_name(int fd);
//char	*get_champ_comment(int fd);
//char	*get_champ_code(int fd);


#endif
