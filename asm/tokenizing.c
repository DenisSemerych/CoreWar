#include "asm.h"

t_list *create_arg_list(t_list *lables, t_list *instructions, t_list *info)
{
    return NULL;
}


void    save_info(char **file, t_list **info, int *line_nbr)
{
    t_list *command;
    char *command_info;

    command = ft_lstnew(NULL, 0);
    command_info = NULL;
    if (!ft_strncmp(*file, NAME_CMD_STRING, 5) && *file + 5)
        command->content_size = NAME;
    else if (!ft_strncmp(*file, COMMENT_CMD_STRING, 8) && *file + 8)
        command->content_size = COMMENT;
   // else
     //   error(line_nbr, *file);
}

void    save_instruction(char **file, t_list **instructions, t_list **info, int *line_nbr)
{

}


t_list *tokenize(char *file)
{
    int     line_nbr;
    t_list *instructions;
    t_list *lables;
    t_list *info;

    instructions = NULL;
    lables = NULL;
    info = NULL;
    line_nbr = 1;
    while (file)
    {
        if (*file == '.')
           save_info(&file, &info, &line_nbr);
        if (*file == '#')
            while (*file != '\n')
                file++;
        if (*file == '\n' && *file++)
            line_nbr++;
        save_instruction(&file, &instructions, &info, &line_nbr);
    }
    return (create_arg_list(lables, instructions, info));
}

