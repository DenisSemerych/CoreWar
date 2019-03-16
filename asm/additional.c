#include "asm.h"
void		put_err_msg_exit(char *str)
{
    printf("%s", MAG);
    ft_putendl_fd(str, 2);
    exit(0);
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

    num = 0;
    tmp = (char *)str;
    check_for_add_sym(tmp);
    while (*tmp > 47 && *tmp < 58)
    {
        num = (*tmp - 48) + (num * 10);
        if (num > 2147483647)
            put_err_msg_exit("Error: number more int-max value");
        tmp++;
    }
    return ((int)(num));
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
