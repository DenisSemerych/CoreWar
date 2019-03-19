#include "vm.h"

void	codage_proc(t_process *process, unsigned char codage)
{
	unsigned char	args[3];
	int 			i;

	if (g_op_tab[process->op_code].octal)
	{
		args[0] = codage & (unsigned char)0b11000000 >> 6;
		args[1] = codage & (unsigned char)0b00110000 >> 4;
		args[2] = codage & (unsigned char)0b00001100 >> 2;
		i = -1;
		while (++i < 3)
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
	{
		process->op_args_type[0] = T_DIR;
		process->op_args_type[1] = 0;
		process->op_args_type[2] = 0;
	}
}

int		write_args(t_data *data, t_process *process)
{
	int	offset;
	int	to_skip;
	int pos;
	int i;

	offset = 1;
	to_skip = 1 + process->op_args_type[0] + process->op_args_type[1] + process->op_args_type[2];
	i = 0;
	while (i < g_op_tab[process->op_code].nb_arg)
	{
		if (!(process->op_args_type[i] & g_op_tab[process->op_code].args[i]))
			return (to_skip);
		if (process->op_args_type[i] & g_op_tab[process->op_code].args[i])
		{
			pos = get_absolute_cord(process->position, offset);
			process->op_args_pointers[i] = &(data->board[pos]);
			offset = pos - process->position + process->op_args_type[i];
		}
	}
	return (offset);
}

