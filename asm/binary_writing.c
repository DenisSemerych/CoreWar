#include "asm.h"

void       write_args(unsigned char **file, t_inst *inst, size_t *written_bytes, t_list *lables)
{

}

void       write_argstype(unsigned char **file, t_inst *inst, size_t *written_bytes)
{
    int    count;
    unsigned char code;

    count = -1;
    code = 0;
    while(count++ < 2)
    {
        if (count < inst->nb_arg)
            code = code | inst->types[count];
        code = code << 2;
    }
    (*file)[*written_bytes] = code;
    *written_bytes += 1;
}

void       write_champ_code(t_list *instructions, unsigned char **file, size_t *written_bytes, t_list *lables)
{
    int    index;
    t_inst *inst;

    while (instructions)
    {
        inst = instructions->content;
        index = give_op_index(inst->name);
        (*file)[*written_bytes] = g_op_tab[index].opcode;
        *written_bytes += 1;
        if (g_op_tab[index].octal)
            write_argstype(file, inst, written_bytes);
        write_args(file, inst, written_bytes, lables);
        instructions = instructions->next;
    }
}


size_t     code_size(t_list *instructions)
{
    size_t size;
    int index;
    size_t current_size;
    t_inst *inst;
    int i;

    size = 0;
    while (instructions)
    {
        inst = instructions->content;
        current_size = 0;
        index = give_op_index(inst->name);
        i = -1;
        inst->nb_arg == 1 && inst->types[0] == T_DIR ? 0 :
        current_size++;
        while (i++ < inst->nb_arg)
        {
            if ((inst->types[i] == T_DIR && g_op_tab[index].label == 2) ||
            inst->types[i] == T_IND)
                current_size += 2;
            else if (inst->types[i] == T_DIR && g_op_tab[index].label == 4)
                current_size += 4;
            else
                current_size += 1;
        }
        size += current_size;
        instructions->content_size = current_size;
        instructions = instructions->next;
    }
    return (size);
}


void    write_info(t_list *info, unsigned char **file, size_t *written_bytes, size_t code_size)
{
    t_list *crawler;
    unsigned size;

    crawler = info;
    while (crawler->content_size != NAME)
        crawler = crawler->next;
    if (ft_strlen(crawler->content) > PROG_NAME_LENGTH)
        put_err_msg_exit("Name is too long");
    ft_memcpy((*file + *written_bytes), crawler->content, ft_strlen(crawler->content));
    *written_bytes += 132;
    size = reverse_byte(code_size);
    ft_memcpy(*file + *written_bytes, &size, 4);
    crawler = info;
    *written_bytes += 4;
    while (crawler->content_size != COMMENT)
        crawler = crawler->next;
    if (ft_strlen(crawler->content) > COMMENT_LENGTH)
        put_err_msg_exit("Comment is too long");
    ft_memcpy(*file + *written_bytes, crawler->content, ft_strlen(crawler->content));
    *written_bytes += COMMENT_LENGTH + 4;
}


void    write_binary(t_list *arguments)
{
    unsigned char *file;
    unsigned tmp;
    int fd;
    size_t writen_bytes;

    fd = open("test.cor", O_WRONLY | O_CREAT | O_RDONLY);
    tmp = reverse_byte(COREWAR_EXEC_MAGIC);
    writen_bytes = 4;
    file = ft_memalloc(10000);
    ft_memcpy(file, &tmp, writen_bytes);
    write_info(arguments->next->next->content, &file, &writen_bytes, code_size(arguments->content));
    write_champ_code(arguments->content, &file, &writen_bytes, arguments->next->content);
    write(fd, file, writen_bytes);
}
