#include "asm.h"

unsigned lable_addres(t_list *lables, char *arg)
{
    t_lable *lable;
    size_t size_arg;
    size_t size_lbl;

    ft_strchr(arg, '%') ? (arg += 2) :
    (arg += 1);
    while (lables)
    {
        size_arg = ft_strlen(arg);
        lable = lables->content;
        size_lbl = ft_strlen(lable->name);
        if (ft_strnequ(arg, lable->name, size_lbl > size_arg ? size_lbl : size_arg))
            return (lable->opp ? lable->addr : g_size);
        lables = lables->next;
    }
    put_err_msg_exit("No such lable");
}


unsigned give_label_addres(t_list *lables, t_inst *inst, size_t *champ_code)
{
    return (lable_addres(lables, inst->args[lables->content_size]) - *champ_code);
}

size_t      write_arg(unsigned char **file, t_inst *inst, t_list *lables, size_t *champ_code)
{
    unsigned tmp;
    size_t   incr;
    int count;

    count = lables->content_size;
    if (inst->types[count] == T_REG && (incr = 1))
        (*file)[(g_written_bytes)++] = (unsigned char)ft_atoi(inst->args[count] + 1);
    else
    {
        if (!ft_strchr(inst->args[count], '%'))
            tmp = reverse_byte((unsigned)ft_atoi(inst->args[count]));
        else if (!ft_strchr(inst->args[count], ':'))
            tmp = reverse_byte((unsigned)ft_atoi(inst->args[count] + 1));
        else
            tmp = reverse_byte(give_label_addres(lables, inst, champ_code));
        if (ft_strchr(inst->args[count], '%') && g_op_tab[give_op_index(inst->name)].label == 4 &&
        (incr = 4))
        {
                ft_memcpy(*file + g_written_bytes, &tmp, 4);
                g_written_bytes += 4;
        }
        else if ((incr = 2))
        {
            tmp >>= 16;
            ft_memcpy(*file + g_written_bytes, &tmp, 2);
            g_written_bytes += 2;
        }
    }
    return (incr);
}

size_t       write_argstype(unsigned char **file, t_inst *inst)
{
    int    count;
    unsigned char code;

    count = 0;
    code = 0;
    while(count < 3)
    {
        if (inst->types[count] != T_IND && inst->types[count]!= T_DIR &&
        inst->types[count] != T_REG)
            ;
        else if (inst->types[count] == T_IND)
            code = code | IND_CODE;
        else if (inst->types[count] == T_DIR)
            code = code | DIR_CODE;
        else if (inst->types[count])
            code = code | REG_CODE;
        code = code << 2;
        count++;
    }
    (*file)[g_written_bytes++] = code;
    return (1);
}

void       write_champ_code(t_list *instructions, unsigned char **file, t_list *lables, size_t *champ_code)
{
    int    index;
    t_inst *inst;
    int     count;
    size_t  incr;
    while (instructions)
    {
        incr = 0;
        count = -1;
        inst = instructions->content;
        index = give_op_index(inst->name);
        (*file)[g_written_bytes++] = g_op_tab[index].opcode;
        incr += 1;
        if (g_op_tab[index].octal)
        {
            incr += write_argstype(file, inst);
        }
        while (++count < inst->nb_arg)
        {
            lables->content_size = count;
            incr += write_arg(file, inst, lables, champ_code);
        }
        *champ_code += incr;
        instructions = instructions->next;
    }
}


size_t     code_size(t_list *instructions)
{
    int index;
    size_t current_size;
    t_inst *inst;
    int i;

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
        inst->lable ? (inst->lable->addr = g_size) : 0;
        g_size += current_size;
        inst->size = current_size;
        instructions = instructions->next;
    }
    return (g_size);
}


void    write_info(t_list *info, unsigned char **file, size_t code_size)
{
    t_list *crawler;
    unsigned size;

    crawler = info;
    while (crawler->content_size != NAME)
        crawler = crawler->next;
    if (ft_strlen(crawler->content) > PROG_NAME_LENGTH)
        put_err_msg_exit("Name is too long");
    ft_memcpy((*file + g_written_bytes), crawler->content, ft_strlen(crawler->content));
    g_written_bytes += 132;
    size = reverse_byte(code_size);
    ft_memcpy(*file + g_written_bytes, &size, 4);
    crawler = info;
    g_written_bytes += 4;
    while (crawler->content_size != COMMENT)
        crawler = crawler->next;
    if (ft_strlen(crawler->content) > COMMENT_LENGTH)
        put_err_msg_exit("Comment is too long");
    ft_memcpy(*file + g_written_bytes, crawler->content, ft_strlen(crawler->content));
    g_written_bytes += COMMENT_LENGTH + 4;
}


void    write_binary(t_list *arguments)
{
    unsigned char *file;
    unsigned tmp;
    int fd;
    size_t champ_code;

    fd = open(g_champ_name, O_RDWR | O_CREAT, 0666);
    tmp = reverse_byte(COREWAR_EXEC_MAGIC);
    g_written_bytes = 4;
    file = ft_memalloc(10000);
    ft_memcpy(file, &tmp, g_written_bytes);
    write_info(arguments->next->next->content, &file, code_size(arguments->content));
    champ_code = 0;
    write_champ_code(arguments->content, &file, arguments->next->content, &champ_code);
    ft_printf("Writting output at %s\n", g_champ_name);
    write(fd, file, g_written_bytes);
    close(fd);
}
