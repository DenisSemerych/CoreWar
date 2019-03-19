#include "vm.h"

int 	read_arg(t_process *process, int argnum)
{

}

int 	write_arg(t_process *process, int argnum, int value)
{

}

void	write_data(int position, int data)
{

}

void	live(t_process *process, int cycle_num)
{
	if (read_arg(process, 0) == process->parent_number)
		process->alive_cycle = cycle_num;
}

void	st(t_process *process, t_data *data)
{
	write_arg(process, 1, read_arg(process, 0));
}

void	ld(t_process *process, t_data *data)
{
	write_arg(process, 1, read_arg(process, 0));
	process->carry = (read_arg(process, 1) == 0);
}

void	lld(t_process *process, t_data *data)
{
	write_arg(process, 1, read_arg(process, 0));
	process->carry = (read_arg(process, 1) == 0);
	//ne usekat' posiciyu pri t_ind
}

void	sub_add(t_process *process)
{
	if (process->op_code == 3)
		write_arg(process, 2, read_arg(process, 0) + read_arg(process, 1));
	else
		write_arg(process, 2, read_arg(process, 0) - read_arg(process, 1));
	process->carry = (read_arg(process, 2) == 0);

}

void	and_or_xor(t_process *process)
{
	if (process->op_code == 5)
		write_arg(process, 2, read_arg(process, 0) & read_arg(process, 1));
	else if (process->op_code == 6)
		write_arg(process, 2, read_arg(process, 0) | read_arg(process, 1));
	else
		write_arg(process, 2, read_arg(process, 0) ^ read_arg(process, 1));
	process->carry = (read_arg(process, 2) == 0);
}

void	zjmp(t_process *process)
{
	if (process->carry)
		process->position = (process->position + read_arg(process, 0) % IDX_MOD) % MEM_SIZE;
	//ne propuskat mesto!!!
}

void	ldi(t_process *process)
{
	write_arg(process, 2, process->position + (read_arg(process, 0) + read_arg(process, 1)) % IDX_MOD);
}

void	sti(t_process *process)
{
	write_data(process->position + (read_arg(process, 1) + read_arg(process, 2)) % IDX_MOD, read_arg(process, 0));
}

void	fork_(t_process *process, t_data *data)
{
	t_process new_process;

	bzero(&new_process, sizeof(t_process));
	ft_memcpy(&new_process.reg, process->reg, sizeof(process->reg));
	new_process.carry = process->carry;
	new_process.alive_cycle = process->alive_cycle;
	new_process.position = read_arg(process, 0) % IDX_MOD;
	ft_lstadd(&data->processes, ft_lstnew(&new_process, sizeof(t_process)));
}

void	execute_opeartion(t_process *process, t_data *data)
{
	if (process->op_code == 0)
		live(process, data->cycle);
	else if (process->op_code == 1)
		ld(process, data);
	else if (process->op_code == 2)
		st(process, data);
	else if (process->op_code < 5)
		sub_add(process);
	else if (process->op_code < 8)
		and_or_xor(process);
	else if (process->op_code == 9)
		zjmp(process);
	else if (process->op_code == 10)
		ldi(process);
	else if (process->position == 11)
		sti(process);
	else if (process->position == 12)
		fork_(process, data);
	else if (process->position == 13)
		lld(process, data);
}