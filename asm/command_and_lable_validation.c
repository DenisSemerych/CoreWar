#include "asm.h"

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
    char *command;
    char *crawler;
    t_inst *inst;
    char *op_name_crawler;

    command = ft_strsub(line, 0, ft_strchr(line, '\n') - line);
    crawler = command;
    inst = (t_inst *)malloc(sizeof(t_inst));
    inst->lable = NULL;
    inst->name = op->name;
    while (IS_SEPARATOR(*crawler))
        crawler++;

    return (NULL);
}