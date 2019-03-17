#ifndef ASMCW_ASM_H
#define ASMCW_ASM_H
#include <fcntl.h>
#include "op.h"
#include <stdio.h>
#include "../libft/libft.h"
#define NAME 1
#define COMMENT 2
# define RED   "\x1B[31m"
# define CYN   "\x1B[36m"
# define RESET "\x1B[0m"
# define MAG   "\x1B[35m"
#define IS_SEPARATOR(a) (a == ' ' | '\t' | '\v')
#define SRC_NOT_READ(name) printf("%sCan't read source file %s%s\n",CYN, RED, name, RESET); exit(0)
#define OP(index)	g_op_tab[index]
#define IS_COMMENT(file) (file == COMMENT_CHAR || file ==  ALT_COMMENT_CHAR)

typedef struct s_lable t_lable;

typedef struct s_inst
{
    char *name;
    unsigned char nb_arg;
    void    *arg1;
    void    *arg2;
    void    *arg3;
    t_lable *lable;

}          t_inst;
typedef struct s_lable
{
    char *name;
    t_inst *opp;
}              t_lable;

char *read_from_file(char *file_name);
t_list    *tokenize(char *file);
void	free_str_arr(char **arr, int size);
int						count_size(char **arr);
void		put_err_msg_exit(char *str);
t_list		*add_to_the_end_of_list(t_list *head, t_list *new);
t_list *validate_command(t_list **lables, t_op *op, int *line_nbr, char *crawler);
size_t validate_lable(t_list **lables, char *line, int *line_nbr);
int         full(t_list *info);
t_list		*find_last(t_list *head);
void    give_op_lable(t_list *op, t_list **lables);
#endif
