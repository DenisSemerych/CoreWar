#include "asm.h"

void      check_filename(char *path)
{
    char **splited;
    char *name;


    splited = ft_strsplit(path, '/');
    name = ft_strdup(splited[count_size(splited) - 1]);
    free_str_arr(splited, count_size(splited));
    splited = ft_strsplit(name, '.');
    if (!ft_strequ("s", splited[count_size(splited) - 1]))
        error_function("File extension must be .s", NULL, path);
    g_champ_name = ft_strdup(path);
    g_champ_name = realloc(g_champ_name, ft_strlen(path) + 2);
    ft_strcpy(g_champ_name + (ft_strlen(path) - 1), "cor");
    free_str_arr(splited, count_size(splited));
    free(name);
}

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
        error_function("Error in reading", NULL, file_name);
    while ((rd = read(fd, buff, BUFF_SIZE)))
    {
        buff[rd] = '\0';
        file = (char *)realloc(file, ft_strlen(file) + rd + 1);
        ft_strcat(file, buff);
    }
    return (file);
}
