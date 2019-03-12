
#include "asm.h"


int main(int argc, char **argv)
{
    int i;
    t_list *file;

    i = 0;
    file = NULL;
    if (!argc)
        return 1;
        //print_usage();
    while (++i < argc)
    {
        file = read_from_file(argv[i]);
//        while (file)
//        {
//            ft_printf("line #%d %s\n", file->content_size, file->content);
//            file = file->next;
//        }
//        file = tokenize(file);
    }
}
