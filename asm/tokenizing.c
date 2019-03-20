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
    while (lables)
    {
        t_lable *to_print = lables->content;
        printf("%s\n", to_print->name);
        t_inst *inst = to_print->opp;
        printf("%s %s\n", inst->name, inst->lable->name);
        lables = lables->next;
    }
    while (instructions)
    {
        t_inst *pr = instructions->content;
        printf("%s%s\n%s", MAG, pr->name, RESET);
        printf("\nNumber:%d\n", pr->nb_arg);
        int i = 0;
        while (i < pr->nb_arg)
            printf(" argument:%s", pr->args[i++]);
        instructions = instructions->next;
        printf("\n");
    }
//    while (info)
//    {
//
//    }
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
    skip_separators(file);
    *(*file) != '\"' ? put_err_msg_exit("Error expected \"") : ((*file)++);
    *file = *file + write_string_tokken(command, file, line_nbr);
    printf("Here is in command %s\n", command->content);
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
    if (is_lable(crawler))
       crawler += validate_lable(lables, crawler, line_nbr);
    if (is_free(crawler))
    {
        *file += crawler - line;
        return ;
    }
    while (i++ < 15)
    {
        printf("%s haystack looking for %s\n", crawler, g_op_tab[i].name);
        if (ft_strstr(crawler, g_op_tab[i].name))
            op = &g_op_tab[i];
    }
    if (!op)
    {
        free(line);
        put_err_msg_exit("Error in line");
    }
   *instructions = add_to_the_end_of_list(*instructions,validate_command(op, line_nbr, crawler));
    give_op_lable(find_last(*instructions), lables);
    *file += ft_strlen(line);
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
    while (*file)
    {
        if (*file == '.')
           save_info(&file, &info, &line_nbr);
        skip_separators(&file);
        if (*file == '\n' && *file++)
            line_nbr++;
        skip_comment(&file);
        if (*file != '\0')
            full(info)  ? save_instruction(&file, &instructions, &lables, &line_nbr) : 0;
    }
    printf("Lines = %d\n", line_nbr);
    return (create_arg_list(lables, instructions, info));
}

