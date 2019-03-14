#include "asm.h"

t_list *tokenize(char *file)
{
    int     line_nbr;
    t_list *instructions;
    t_list *lables;
    t_list *info;

    while (file)
    {
        if (*file == '.')
           validate_info(&file, &commands, &info);
        if (*file == '#')
        {
            while (*file != '\n')
                file++;
        }
        if (*file == '\n' && *file++)
            line_nbr++;
        validate_instruction(&file, &instructions, &info, &line_nbr);
    }
    return (create_arg_list(lables, commands, info));
}

