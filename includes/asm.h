/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 10:30:23 by dsemeryc          #+#    #+#             */
/*   Updated: 2019/03/27 11:57:48 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include <fcntl.h>
# include "op.h"
# include "../libft/libft.h"
# define NAME 1
# define COMMENT 2
# define RED  		"\x1B[31m"
# define CYN		"\x1B[36m"
# define FAIL		"\033[91m"
# define RESET		"\x1B[0m"
# define UNDR		"\033[4m"
# define GRN		"\033[92m"
# define BOLD		"\033[1m"
# define IS_SEPARATOR(a) (a == ' ' || a == '\t' || a == '\v')
# define A(n) ft_printf("%sCan't read source file %s%s\n",CYN, RED, n)
# define SRC_NOT_READ(name) A(name); exit(0)
# define IS_COMMENT(file) (file == COMMENT_CHAR || file ==  ALT_COMMENT_CHAR)

extern size_t			g_written_bytes;
extern unsigned			g_size;
extern int				g_count;
extern char				*g_champ_name;

typedef struct			s_inst
{
	char				*name;
	unsigned char		nb_arg;
	char				*args[3];
	t_arg_type			types[3];
	size_t				size;
	struct s_lable		*lable;
}						t_inst;

typedef struct			s_lable
{
	char				*name;
	unsigned			addr;
	t_inst				*opp;
}						t_lable;

int						only_comment(char *file);
void					skip_comment(char **file);
void					skip_separators(char **file);
t_list					*tokenize(char *file);
void					free_str_arr(char **arr, int size);
int						count_size(char **arr);
int						spec_atoi(const char *str);
t_list					*add_to_the_end_of_list(t_list *head, t_list *new);
t_list					*validate_command(t_op *op, int *line_nbr, char *line);
size_t					validate_lable(t_list **lables,
						char *line, int *line_nbr);
int						full(t_list *info);
t_list					*find_last(t_list *head);
void					give_op_lable(t_list *op, t_list **lables);
int						is_free(char *line);
int						is_label(char *line, int *line_nbr);
void					save_instruction(char **file, t_list **instructions,
						t_list **lables, int *line_nbr);
void					write_binary(t_list **arguments);
unsigned int			reverse_byte(unsigned int byte);
int						give_op_index(char *op_name);
void					error_function(char *msg, int *line_nbr,
						char *line, int check);
t_op					*find_op(char **crawler);
unsigned char			check_reg_num(int num, char *arg);
unsigned				give_label_address(t_list **lables,
						t_inst *inst, unsigned *champ_code);
unsigned				code_size(t_list *instructions);
void					write_in_file(unsigned tmp, t_inst *inst,
						unsigned *incr, unsigned char **file);
t_list					*create_arg_list(t_list **lables,
						t_list *instructions, t_list *info);
void					cut_comment(char **line, char **file);
void					check_commas(char *line, int *line_nbr, int number);
t_arg_type				define_type(char *command, int *line_nbr);
void					check_file(char *file, int *line_nbr);
#endif
