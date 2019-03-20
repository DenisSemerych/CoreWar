#include "asm.h"

void    parse_arg(t_inst **inst, t_op *op, int *line_nbr, char *crawler)
{
    char **args;
    t_arg_type type;
    int  count;
    char *trimed;

    args = ft_strsplit(crawler, ',');
    count = 0;
    if (count_size(args) != op->nb_arg)
        put_err_msg_exit("Error in number of arguments");
    while (count < count_size(args))
    {
        trimed = ft_strtrim(args[count]);
        if (*trimed == '%')
            type = T_DIR;
        else if (*trimed == 'r')
            type = T_REG;
        else
            type = T_IND;
        if (op->args[count] & type)
            (*inst)->args[count] = args[count];
        else
            put_err_msg_exit("Wrong argument type for command");
        count++;
    }
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
            inst->lable = lable;
        }
        crawler = crawler->next;
    }
}

size_t validate_lable(t_list **lables, char *line, int *line_nbr)
{
    char *lablel;
    t_list *new;
    t_lable *save;
    char *crawler;

    lablel = ft_strsub(line, 0, ft_strchr(line, ':') - line);
    crawler = lablel;
    while (*crawler)
    {
        if (!ft_strchr(LABEL_CHARS, *crawler))
            put_err_msg_exit("Wrong char in lable name");
        crawler++;
    }
    new = ft_lstnew(NULL, 0);
    save = (t_lable *)malloc(sizeof(t_lable));
    save->name = lablel;
    save->opp = NULL;
    new->content = save;
    *lables = add_to_the_end_of_list(*lables, new);
    return (ft_strlen(lablel) + 1);
}


t_list *validate_command(t_list **lables, t_op *op, int *line_nbr, char *line)
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
    parse_arg(&inst, op, line_nbr, crawler);
    inst->lable = NULL;
    command = ft_lstnew(NULL, 0);
    command->content = inst;
    return (command);
}