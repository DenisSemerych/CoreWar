#include "asm.h"

void      check_filename(char *path)
{
    char **splited;
    char *name;


    splited = ft_strsplit(path, '/');
    name = ft_strdup(splited[count_size(splited) - 1]);
    free_str_arr(splited, count_size(splited));
    splited = ft_strsplit(name, '.');
    if (count_size(splited) == 1 || ft_strcmp(splited[1], "s"))
    {
        printf("%s%s invalid. ",RED, name);
        put_err_msg_exit("File extension must be .s");
    }
    else if (count_size(splited) != 2)
    {
        printf("%s%s invalid. ",RED, name);
        put_err_msg_exit(" File can have only one '.'(dot) in name");
    }
    g_champ_name = ft_strdup(path);
    g_champ_name = realloc(g_champ_name, ft_strlen(path) + 2);
    ft_strcpy(g_champ_name + (ft_strlen(path) - 1), "cor");
    //ft_printf("NAME = %s\n", g_champ_name);
    free_str_arr(splited, count_size(splited));
    free(name);
}
//
//void      set_elem(t_list **crawler, int line_nbr, char *line)
//{
//    (*crawler)->content = line;
//    (*crawler)->content_size = line_nbr;
//    (*crawler)->next = ft_lstnew(NULL, 0);
//    (*crawler) = (*crawler)->next;
//}

char *read_from_file(char *file_name)
{
    int fd;
    char *file;
    char  buff[BUFF_SIZE + 1];
    int   rd;

    check_filename(file_name);
    if ((fd = open(file_name, O_RDONLY)) < 0)
    {
        SRC_NOT_READ(file_name);
    }
    file = ft_memalloc(1);
    if (read(fd, buff, 0) != 0)
        put_err_msg_exit("Error in reading file");
    while ((rd = read(fd, buff, BUFF_SIZE)))
    {
        buff[rd] = '\0';
        file = (char *)realloc(file, ft_strlen(file) + rd + 1);
        ft_strcat(file, buff);
    }
    return (file);
}
