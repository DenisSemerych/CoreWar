
#include "asm.h"


int main(int argc, char **argv)
{
    int i;
    char *file;

    i = 0;
    file = NULL;
    if (!argc)
        return 1;
        //print_usage();
    while (++i < argc)
    {
        file = read_from_file(argv[i]);
//        ft_printf(file);
//        while (file)
//        {
//            ft_printf("line #%d %s\n", file->content_size, file->content);
//            file = file->next;
//        }
       // file = tokenize(file);
    }
}
