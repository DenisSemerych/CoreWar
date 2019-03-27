#include "asm.h"

void   check_file(char *file, int *line_nbr)
{
    if (*file != COMMENT_CHAR && *file != ALT_COMMENT_CHAR && !IS_SEPARATOR(*file) && *file != '.' && *file != '\n')
        error_function("Lexical error", line_nbr, file, 0);
}

int    write_string_tokken(t_list *command, char **file, int *line_nbr)
{
    char *crawler;
    int size;
    char *info;

    crawler = *file;
    size = 0;
    while (crawler && *crawler != '\"')
    {
        *crawler == '\n' ? (*line_nbr)++ : 0;
        crawler++;
        size++;
    }
    !crawler ? error_function("END (null) don`t close brackets", line_nbr, *file, 0) : size++;
    info = (char *)malloc(size);
    info[size-1] = '\0';
    ft_strncpy(info, *file, size-1);
    command->content = info;
    return (size);
}


t_list *create_arg_list(t_list **lables, t_list *instructions, t_list *info)
{
    t_list *new;


    if (!*lables && !instructions)
        error_function("Add at least one label", NULL, "No champ code and no label", 0);
    new = ft_lstnew(NULL, 0);
    new->next = ft_lstnew(NULL, 0);
    new->next->next = ft_lstnew(NULL, 0);
    new->content = instructions;
    new->content_size = 1;
    new->next->content = *lables;
    new->next->content_size = 2;
    new->next->next->content = info;
    new->next->next->content_size = 3;
    return (new);
}


void    save_info(char **file, t_list **info, int *line_nbr)
{
    t_list *command;

    command = ft_lstnew(NULL, 0);
    if (!ft_strncmp(*file, NAME_CMD_STRING, 5) && (*file = *file + 5))
        command->content_size = NAME;
    else if (!ft_strncmp(*file, COMMENT_CMD_STRING, 8) && (*file = *file + 8))
        command->content_size = COMMENT;
    else
        error_function("Not supported command", line_nbr, *file, 0);
    skip_separators(file);
    *(*file) != '\"' ? error_function("Error in command line", line_nbr, *file, 0) : ((*file)++);
    *file = *file + write_string_tokken(command, file, line_nbr);
    ft_lstadd(info, command);
}

void    cut_comment(char **line, char **file)
{
    char *cut;

    cut = NULL;
    if (ft_strchr(*line, COMMENT_CHAR))
        cut = ft_strsub(*line, 0, ft_strchr(*file, COMMENT_CHAR) - *file);
    else if (ft_strchr(*line, ALT_COMMENT_CHAR))
        cut = ft_strsub(*line, 0, ft_strchr(*file, ALT_COMMENT_CHAR) - *file);
    if (cut)
    {
        free(*line);
        *line = cut;
    }
}

void    save_instruction(char **file, t_list **instructions, t_list **lables, int *line_nbr)
{
    t_op *op;
    char *line;
    char *crawler;

    line = ft_strsub(*file, 0, ft_strchr(*file, '\n') - *file);
    cut_comment(&line, file);
    crawler = line;
    if (is_lable(crawler, line_nbr))
       crawler += validate_lable(lables, crawler, line_nbr);
    if (is_free(crawler))
    {
        *file += crawler - line;
        free(line);
        return ;
    }
    op = find_op(&crawler);
    if (!op)
        error_function("Syntax error", line_nbr, *file, 0);
   *instructions = add_to_the_end_of_list(*instructions,validate_command(op, line_nbr, crawler));
    give_op_lable(find_last(*instructions), lables);
    *file += ft_strlen(line);
    free(line);
}

t_list *tokenize(char *file)
{
    int     line_nbr;
    t_list *instructions;
    t_list *labels;
    t_list *info;
    t_list *args;

    instructions = NULL;
    labels = NULL;
    info = NULL;
    line_nbr = 1;
    while (*file)
    {
        if (*file == '.')
           save_info(&file, &info, &line_nbr);
        skip_separators(&file);
        if (*file == '\n' && *file++)
            line_nbr++;
        skip_comment(&file);
        skip_separators(&file);
        if (*file != '\0' && ft_strchr(file, '\n'))
            full(info) ? save_instruction(&file, &instructions, &labels, &line_nbr) :
            check_file(file, &line_nbr);
        else if (*file != '\0' && !ft_strchr(file, '\n'))
            error_function("Missing newline after instruction", NULL, file, 1);
    }
    args = create_arg_list(&labels, instructions, info);
    return (args);
}

