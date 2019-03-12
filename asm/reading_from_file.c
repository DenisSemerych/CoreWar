#include "asm.h"

void      check_filename(char *path)
{
    char **splited;
    char *name;

    splited = ft_strsplit(path, '/');
    name = ft_strdup(splited[count_size(splited) - 1]);
    free_str_arr(splited, count_size(splited));
    splited = ft_strsplit(name, '.');
    if (count_size(splited) == 1)
    {
        ft_printf("%s%s invalid. ", RED, name);
        put_err_msg_exit(" File extension must be .s");
    }
    if (count_size(splited) != 2)
    {
        ft_printf("%s%s invalid. ",RED, name);
        put_err_msg_exit(" File can have only one '.'(dot) in name");
    }
    if (ft_strcmp(splited[1], "s"))
    {
        ft_printf("%s invalid. ",RED, name);
        put_err_msg_exit("File extension must be .s");
    }
    free_str_arr(splited, count_size(splited));
}


t_list    *read_from_file(char *file_name)
{
    int fd;
    char *line;
    t_list *file;
    t_list *crawler;
    int    line_nbr;

    check_filename(file_name);
    if ((fd = open(file_name, O_RDONLY)) < 0)
    {
        SRC_NOT_READ(file_name);
    }
    line = NULL;
    file = ft_lstnew(NULL, 0);
    crawler = file;
    line_nbr = 1;
    while (get_next_line(fd, &line) > 0 )
    {
        if (ft_strcmp(line,""))
        {
            crawler->content = line;
            crawler->content_size = line_nbr;
            crawler->next = ft_lstnew(NULL, 0);
            crawler = crawler->next;
        }
        line_nbr++;
    }
    crawler->content = "EOF";
    crawler->content_size = line_nbr;
    return (file);
}
