
#include "asm.h"


int main(int argc, char **argv)
{
    int i;
    char *file;
    t_list *arguments_list;

    i = 0;
    file = NULL;
    if (!argc)
        return 1;
        //print_usage();
    while (++i < argc)
    {
        file = read_from_file(argv[i]);
        arguments_list = tokenize(file);
    }
}
