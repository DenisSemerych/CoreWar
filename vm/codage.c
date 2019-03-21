#include "vm.h"

void	codage_proc(t_process *process, unsigned char codage)
{
	unsigned char	args[3];
	int 			i;

	process->op_args_type[0] = 0;
	process->op_args_type[1] = 0;
	process->op_args_type[2] = 0;
	if (g_op_tab[process->op_code].octal)
	{
		args[0] = (codage & (unsigned char)0b11000000) >> 6;
		args[1] = (codage & (unsigned char)0b00110000) >> 4;
		args[2] = (codage & (unsigned char)0b00001100) >> 2;
		i = -1;
		while (++i < g_op_tab[process->op_code].nb_arg)
		{
			if (args[i] == 0b10)
				process->op_args_type[i] = T_DIR;
			else if (args[i] == 0b01)
				process->op_args_type[i] = T_REG;
			else if (args[i] == 0b11)
				process->op_args_type[i] = T_IND;
			else
				process->op_args_type[i] = 0;
		}
	}
	else
		process->op_args_type[0] = T_DIR;
}

int 	get_type_size(t_process *process, int arg_type)
{
	if (arg_type == T_DIR)
		return (g_op_tab[process->op_code].label);
	else if (arg_type == T_IND)
		return (2);
	else if (arg_type == T_REG)
		return (1);
	return (0);
}

int		get_offset(t_process *process)
{
	int	offset;
	int i;

	i = 0;
	offset = 1 + g_op_tab[process->op_code].octal;
	if (ft_strcmp(g_op_tab[process->op_code].name, "zjmp") == 0)
		return (0);
	while (i < g_op_tab[process->op_code].nb_arg)
	{
		if (process->op_args_type[i] == T_DIR)
			offset += g_op_tab[process->op_code].label;
		else
			offset += get_type_size(process, process->op_args_type[i]);
		i++;
	}
	return (offset);
}

void	*get_t_ind_pointer(t_data *data, t_process *process, int arg_num)
{
	unsigned int	new_pos;
	unsigned char	*address;

	address = process->op_args_pointers[arg_num];
	new_pos = *address;
	address++;
	new_pos = (new_pos << 2) + *address;
	if (process->op_code >= 13 && process->op_code <= 15)
		return (&data->board[get_absolute_cord(process->position, new_pos % IDX_MOD)]);
	else
		return (&data->board[get_absolute_cord(process->position, new_pos)]);
}

int		write_args_pointers(t_data *data, t_process *process)
{
	int	offset;
	int pos;
	int i;

	offset = (g_op_tab[process->op_code].octal) ? 2 : 1;
	i = 0;
	while (i < g_op_tab[process->op_code].nb_arg)
	{
		if (process->op_args_type[i] & g_op_tab[process->op_code].args[i])
		{
			pos = get_absolute_cord(process->position, offset);
			process->op_args_pointers[i] = &(data->board[pos]);
			offset = pos - process->position + get_type_size(process, process->op_args_type[i]);
		}
		else
			return (0);
		i++;
	}
	return (1);
}

