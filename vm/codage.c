#include "vm.h"

void	codage_proc(t_process *process, unsigned char codage)
{
	unsigned char	args[3];
	int 			i;

	args[0] = codage & (unsigned char)0b11000000 >> 6;
	args[1] = codage & (unsigned char)0b00110000 >> 4;
	args[2] = codage & (unsigned char)0b00001100 >> 2;
	i = -1;
	while (++i < 3)
	{
		if (args[i] == 0b10)
			process->op_args[i] = T_DIR;
		else if (args[i] == 0b01)
			process->op_args[i] = T_REG;
		else if (args[i] == 0b11)
			process->op_args[i] = T_IND;
		else
			process->op_args[i] = 0;
	}
}