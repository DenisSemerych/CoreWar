#include "vm.h"

void	live(t_process *process, int cycle_num)
{
	if (process->op_args == process->parent_number)
		process->alive_cycle = cycle_num;
}

void	st(t_process *process, t_data *data)
{
	if (process->op_args_type[1] == T_REG)
		process->reg[process->op_args[1]] = process->op_args[0];
	else
		((short*)(&data->board[process->op_args[1]]))[0] = process->op_args[0];

}

void	ld(t_process *process, t_data *data)
{
	process->reg[process->op_args[1]] = (process->op_args_type[0] == T_DIR) ? process->op_args[0] : process->op_args[0];


}

void	subadd(t_process *process)
{
	if (process->op_code == 3)
		process->reg[process->op_args[2]] = process->reg[process->op_args[0]] + process->reg[process->op_args[1]];
	else
		process->reg[process->op_args[2]] = process->reg[process->op_args[0]] - process->reg[process->op_args[1]];
	process->carry = (process->reg[process->op_args[2] == 0]) ? 1 : 0;

}

void	bit(t_process *process)
{
	if (process->op_code == 5)
		process->reg[process->op_args[2]] = process->op_args[0] & process->op_args[1];
	else if (process->op_code == 6)
		process->reg[process->op_args[2]] = process->op_args[0] | process->op_args[1];
	else
		process->reg[process->op_args[2]] = process->op_args[0] ^ process->op_args[1];
	process->carry = (process->reg[process->op_args[2] == 0]) ? 1 : 0;
}

void	zjmp(t_process *process)
{
	if (process->carry)
		process->position += process->op_args[0];
}

void	ldi(t_process *process)
{
	process->reg[process->op_args[2]] = (process->op_args[0] + process->op_args[1]) % IDX_MOD;
}

void	sti(t_process *process)
{
	

}

void	execute_opeartions(int op_code, t_data *data, t_process *process)
{
	if (process->op_code == 0)
		live(process, data->cycle);
	else if (process->op_code == 1)
		ld(process, data);
	else if (process->op_code == 2)
		st(process, data);
	else if (process->op_code < 5)
		subadd(process);
	else if (process->op_code < 8)
		bit(process);
	else if (process->op_code == 9)
		zjmp(process);
	else if (process->op_code == 10)
		ldi(process);
}