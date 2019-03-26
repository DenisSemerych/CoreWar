#include "asm.h"
//while (lables)
//{
//t_lable *to_print = lables->content;
//printf("%s\n", to_print->name);
//t_inst *inst = to_print->opp;
//printf("%s %s\n", inst->name, inst->lable->name);
//lables = lables->next;
//}
//while (instructions)
//{
//t_inst *pr = instructions->content;
//printf("%s%s\n%s", MAG, pr->name, RESET);
//printf("\nNumber:%d\n", pr->nb_arg);
//int i = 0;
//while (i < pr->nb_arg)
//printf(" argument:%s", pr->args[i++]);
//instructions = instructions->next;
//printf("\n");
//}



t_op    *find_op(char **crawler)
{
    int count;
    size_t size;
    t_op *op;

    count = 0;
    skip_separators(crawler);
    op = NULL;
    while (count++ < 16)
    {
        size = ft_strlen(g_op_tab[count].name);
        if (ft_strnequ(*crawler, g_op_tab[count].name, size))
            op = &g_op_tab[count];
    }
    return (op);
}


int     give_op_index(char *op_name)
{
    int   count;

    count = 0;
    while (++count < 16)
    {
        if (ft_strequ(op_name, g_op_tab[count].name))
            break;
    }
    return (count);
}

unsigned int		reverse_byte(unsigned int byte)
{
    return (((byte >> 24) & 0x000000ff) |
            ((byte >> 8) & 0x0000ff00) |
            ((byte << 8) & 0x00ff0000) |
            ((byte << 24) & 0xff000000));
}

void        skip_separators(char **file)
{
    while (IS_SEPARATOR(*(*file)))
        (*file)++;
}

void        skip_comment(char **file)
{
    if (IS_COMMENT(*(*file)))
    {
        while (*(*file) && *(*file) != '\n')
            (*file)++;
    }
}


int         is_lable(char *line)
{
    while (*line)
    {
        if (!ft_strchr(LABEL_CHARS, *line))
            break ;
        line++;
    }
    return (*line == LABEL_CHAR ? 1 : 0);
}


int         is_free(char *line)
{
    while (*line)
    {
        if (!IS_SEPARATOR(*line))
            return (IS_COMMENT(*line) ? 1 : 0);
        line++;
    }
    return (1);
}

t_list		*find_last(t_list *head)
{
    t_list *crawler;

    crawler = head;
    while (crawler && crawler->next)
        crawler = crawler->next;
    return (crawler);
}
void		put_err_msg_exit(char *str)
{
    printf("%s", MAG);
    ft_putendl_fd(str, 2);
    exit(0);
}

int						list_count(t_list *list)
{
    int count;

    count = 0;
    while (list)
    {
        count++;
        list = list->next;
    }
    return (count);
}

int         full(t_list *info)
{
    int check;

    check = 0;
    while (info)
    {
        if (info->content_size == NAME)
            check++;
        else if (info->content_size == COMMENT)
            check++;
        info = info->next;
    }
    return (check == 2 ? 1 : 0);
}



t_list		*add_to_the_end_of_list(t_list *head, t_list *new)
{
    t_list	*crawler;

    crawler = head;
    if (!crawler)
        return (new);
    while (crawler->next)
        crawler = crawler->next;
    crawler->next = new;
    return (head);
}

int						count_size(char **arr)
{
    char				**tmp;
    int					size;

    size = 0;
    tmp = arr;
    while (tmp[size])
        size++;
    return (size);
}

void					check_for_add_sym(char *str)
{
    char				*tmp;

    tmp = str;
    while (*tmp)
        !ft_isdigit(*tmp) && *tmp != '-' ?
        (put_err_msg_exit("Error: found non-integer symbol where should be int"))
                          : tmp++;
}

int						spec_atoi(const char *str)
{
    char				*tmp;
    unsigned long int	num;
    int                 sign;

    num = 0;
    tmp = (char *)str;
    sign = ft_strchr(str, '-') ? -1 : 1;
    check_for_add_sym(tmp);
    while ((*tmp > 47 && *tmp < 58) || *tmp == '-')
    {
        if (*tmp != '-')
            num = (*tmp - 48) + (num * 10);
        tmp++;
    }
    return ((int)(num) * sign);
}


void					free_str_arr(char **arr, int size)
{
    int					ind;

    ind = 0;
    while (ind < size)
        ft_strdel(&arr[ind++]);
    free(arr);
    arr = NULL;
}
