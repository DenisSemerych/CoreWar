#include "asm.h"

void    error_function(char *msg, int *line_nbr, char *line)
{
    if (line_nbr)
        ft_printf("%s Error in line #%d\n %s%s\n", RED, *line_nbr, MAG, line, RESET);
    else
        ft_printf("%sFile name: %s%s%s\n", RED, MAG, line, RESET);
    put_err_msg(msg);
}


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
void		put_err_msg(char *str)
{
    printf("%s", MAG);
    ft_putendl_fd(str, 2);
    exit(0);
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

void					free_str_arr(char **arr, int size)
{
    int					ind;

    ind = 0;
    while (ind < size)
        ft_strdel(&arr[ind++]);
    free(arr);
    arr = NULL;
}
