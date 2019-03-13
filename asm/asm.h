#ifndef ASMCW_ASM_H
#define ASMCW_ASM_H
#include <fcntl.h>
#include "op.h"
#include "libft/includes/libft.h"
#include "printf.h"
#define SRC_NOT_READ(name) ft_printf("%sCan't read source file %s%s\n",CYN, RED, name, RESET); exit(0)
typedef struct s_lable
{
    char *name;
    t_list *instruction;
}              t_lable;
char *read_from_file(char *file_name);
t_list    *tokenize(t_list *file);

#endif
