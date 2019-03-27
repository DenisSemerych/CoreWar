#include "asm.h"


void    error_function(char *msg, int *line_nbr, char *line, int check)
{
    if (line_nbr)
        ft_printf("%s Error in line #%d\n", RED, *line_nbr);
    else
        ft_printf("%sError in: ", RED);
    if (check)
        ft_printf("%s%s%s", FAIL, UNDR, line);
    else
    {
        while (*line && *line != '\n')
            ft_printf("%s%s%c",FAIL, UNDR, *line++);
        ft_printf("\n");
    }
    ft_printf(RESET);
    ft_printf(CYN);
    ft_putendl_fd(msg, 2);
    ft_printf(RESET);
    exit(0);
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


int         is_lable(char *line, int *line_nbr)
{
    char *crawler;

    crawler = line;
    while (crawler && *crawler)
    {
        if (!ft_strchr(LABEL_CHARS, *crawler))
            break ;
        crawler++;
    }
    if (ft_strchr(line, ':') && !ft_strchr(line, DIRECT_CHAR) &&
    !ft_strchr(line, SEPARATOR_CHAR)
    && crawler && *crawler != ':')
        error_function("Wrong char in lable name", line_nbr, line, 1);
    return (crawler && *crawler == LABEL_CHAR ? 1 : 0);
}


int         is_free(char *line)
{
    while (line && *line)
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

int         full(t_list *info)
{
    char count_comment;
    char count_name;
    t_list *name;
    t_list *comment;

    count_name = 0;
    count_comment = 0;
    while (info)
    {
        if (info->content_size == NAME && (name = info))
            count_name++;
        else if (info->content_size == COMMENT && (comment = info))
            count_comment++;
        info = info->next;
    }
    if (count_name > 1)
        error_function(".name command need to be only one", NULL, name->content, 0);
    else if (count_comment > 1)
        error_function(".comment command need to be only one", NULL, comment->content, 0);
    return (count_comment + count_name == 2 ? 1 : 0);
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
        (error_function("Lexical error", NULL, str, 0))
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
}
