
#include "asm.h"

void    print_usage()
{
    ft_printf("%sUSAGE: asm source_file\n%s", BOLD, RESET);
    ft_printf("Explanation: will translate your *assembler code to binary\n\n");
    ft_printf("*by assembler code we mean 42-corewar pseudo-assembler\n");
    ft_printf("%s©dsemeryc dzaporoz mmyslyvy yochered 42-Corewar-SBDK%s\n", GRN, RESET);
    exit(0);
}

int main(int argc, char **argv)
{
    char *file;
    t_list *arguments_list;
    int i;

    file = NULL;
    i = 1;
    if (argc == 1)
        print_usage();
    file = read_from_file(argv[i]);
    arguments_list = tokenize(file);
    write_binary(&arguments_list);
}
