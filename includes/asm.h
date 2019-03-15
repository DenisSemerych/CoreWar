#ifndef ASMCW_ASM_H
#define ASMCW_ASM_H
#include <fcntl.h>
#include "op.h"
#include <stdio.h>
#include "../libft/libft.h"
#include "printf.h"
#define NAME 1
#define COMMENT 2
# define RED   "\x1B[31m"
# define CYN   "\x1B[36m"
# define RESET "\x1B[0m"
# define MAG   "\x1B[35m"
#define SRC_NOT_READ(name) printf("%sCan't read source file %s%s\n",CYN, RED, name, RESET); exit(0)
typedef struct s_lable
{
    char *name;
    t_list *opp;
}              t_lable;
typedef struct s_opp
{
    char *name;
    void *arg_1;
    void *arg_2;
    void *arg_3;
}               t_opp;
char *read_from_file(char *file_name);
t_list    *tokenize(char *file);
void	free_str_arr(char **arr, int size);
int						count_size(char **arr);
void		put_err_msg_exit(char *str);
#endif
