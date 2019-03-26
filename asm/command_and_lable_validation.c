#include "asm.h"

char    *give_arg(char *trimed)
{
    size_t size;
    char *crawler;
    char *arg;
    char *crw_2;

    crawler = trimed;
    size = 0;
    while(*crawler)
    {
        if (IS_COMMENT(*crawler))
            break ;
        if (!IS_SEPARATOR(*crawler))
            size++;
        crawler++;
    }
    arg = ft_memalloc(size + 1);
    crawler = trimed;
    crw_2 = arg;
    while (size)
    {
        *crw_2++ = *crawler++;
        size--;
    }
    free(trimed);
    return (arg);
}

void    parse_arg(t_inst **inst, t_op *op, int *line_nbr, char *crawler)
{
    char **args;
    t_arg_type type;
    int  count;
    char *trimed;

    args = ft_strsplit(crawler, ',');
    count = 0;
    while (count < op->nb_arg)
    {
        trimed = ft_strtrim(args[count]);
        trimed = give_arg(trimed);
        if (*trimed == '%')
            type = T_DIR;
        else if (*trimed == 'r')
            type = T_REG;
        else
            type = T_IND;
        op->args[count] & type ? ((*inst)->args[count] = trimed) :
        error_function("Wrong argument type for command", line_nbr, crawler);
        free(args[count]);
        (*inst)->types[count] = type;
        count++;
    }
    if (count != op->nb_arg)
        error_function("Error in number of arguments", line_nbr, crawler);
    free(args);
    (*inst)->nb_arg = op->nb_arg;
}

void    give_op_lable(t_list *op, t_list **lables)
{
    t_inst *inst;
    t_list *crawler;
    t_lable *lable;

    inst = op->content;
    crawler = *lables;
    while (crawler)
    {
        lable = crawler->content;
        if (!lable->opp)
        {
            lable->opp = inst;
            if (!inst->lable)
                inst->lable = lable;
        }
        crawler = crawler->next;
    }
}

size_t validate_lable(t_list **lables, char *line, int *line_nbr)
{
    char *label;
    t_list *new;
    t_lable *save;
    char *crawler;

    label = ft_strsub(line, 0, ft_strchr(line, ':') - line);
    crawler = label;
    while (*crawler)
    {
        if (!ft_strchr(LABEL_CHARS, *crawler))
            error_function("Wrong char in lable name", line_nbr, label);
        crawler++;
    }
    new = ft_lstnew(NULL, 0);
    save = (t_lable *)malloc(sizeof(t_lable));
    save->name = label;
    save->opp = NULL;
    save->addr = g_size;
    new->content = save;
    *lables = add_to_the_end_of_list(*lables, new);
    return (ft_strlen(label) + 1);
}


t_list *validate_command(t_op *op, int *line_nbr, char *line)
{
    char *crawler;
    t_inst *inst;
    char *op_name_crawler;
    t_list *command;

    crawler = line;
    inst = (t_inst *)malloc(sizeof(t_inst));
    inst->lable = NULL;
    inst->name = op->name;
    op_name_crawler = op->name;
    skip_separators(&crawler);
    while (*crawler == *op_name_crawler)
    {
        op_name_crawler++;
        crawler++;
    }
    skip_separators(&crawler);
    if (*crawler == 'r' && !IS_SEPARATOR(*(crawler - 1)))
        error_function("Missing separator before r-arg", line_nbr, line);
    parse_arg(&inst, op, line_nbr, crawler);
    inst->lable = NULL;
    command = ft_lstnew(NULL, 0);
    command->content = inst;
    return (command);
}