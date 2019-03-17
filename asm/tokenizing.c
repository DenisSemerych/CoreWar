#include "asm.h"

int    write_string_tokken(t_list *command, char **file, int *line_nbr)
{
    char *crawler;
    int size;
    char *info;

    crawler = *file;
    size = 0;
    while (crawler && *crawler != '\"')
    {
        *crawler == '\n' ? (*line_nbr)++ : 0;
        crawler++;
        size++;
    }
    !crawler ? put_err_msg_exit("END (null) don`t close brackets") : size++;
    info = (char *)malloc(size);
    info[size-1] = '\0';
    ft_strncpy(info, *file, size-1);
    command->content = info;
    return (size);
}


t_list *create_arg_list(t_list *lables, t_list *instructions, t_list *info)
{
    return NULL;
}


void    save_info(char **file, t_list **info, int *line_nbr)
{
    t_list *command;

    command = ft_lstnew(NULL, 0);
    if (!ft_strncmp(*file, NAME_CMD_STRING, 5) && (*file = *file + 5))
        command->content_size = NAME;
    else if (!ft_strncmp(*file, COMMENT_CMD_STRING, 8) && (*file = *file + 8))
        command->content_size = COMMENT;
    else
        put_err_msg_exit("here");
    while (IS_SEPARATOR(*(*file)))
        (*file)++;
    *(*file) != '\"' ? put_err_msg_exit("Error expected \"") : ((*file)++);
    *file = *file + write_string_tokken(command, file, line_nbr);
  //  printf("Here is in command %s\n", command->content);
    ft_lstadd(info, command);
}

void    save_instruction(char **file, t_list **instructions, t_list **lables, int *line_nbr)
{
    int i;
    t_op *op;
    char *line;
    char *crawler;


    i = -1;
    op = NULL;
    line = ft_strsub(*file, 0,ft_strchr(*file, '\n') - *file);
    crawler = line;
    if (ft_strchr(crawler, ':'))
       crawler += validate_lable(lables, crawler, line_nbr);
    while (i++ < 16)
        if (ft_strstr(OP(i).name, crawler))
            op = &OP(i);
    if (!op)
    {
        free(line);
        return ;
    }
   *instructions = add_to_the_end_of_list(*instructions,validate_command(lables, op, line_nbr, crawler));
    give_op_lable(find_last(*instructions), lables);
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
        if (*file == COMMENT_CHAR | ALT_COMMENT_CHAR)
            while (*file != '\n')
                file++;
        if (*file == '\n' && *file++)
            line_nbr++;
        full(info) ? save_instruction(&file, &instructions, &lables, &line_nbr) : 0;
    }
    return (create_arg_list(lables, instructions, info));
}

