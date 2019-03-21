#include "vm.h"


void	write_data(void *position, int value, t_data *data)
{
	int n;
	unsigned char *p;

	n = 0;
	p = position;
	while (n < 4)
	{
		*p++ = (value << 24) >> 24;
		value >>= 8;
		if (p - data->board > MEM_SIZE)
			p = data->board;
		n++;
	}
}

int 	read_arg(t_process *process, int argnum, t_data *data)
{
	int arg;
	int size;
	int n;
	unsigned char *p;

	n = 0;
	arg = 0;
	p = process->op_args_pointers[argnum];
	size = (process->op_args_type[argnum] == T_DIR) ? g_op_tab[process->op_code].label : process->op_args_type[argnum];
	while (n < size && n < sizeof(int))
	{
		arg <<= 8;
		arg |= (int)*p++;
		if (p - data->board > MEM_SIZE)
			p = data->board;
		n++;
	}
	return ((process->op_args_type[argnum] == T_REG) ? process->reg[arg] : arg);
}

void 	write_arg(t_process *process, int argnum, int value, t_data *data)
{
	if (process->op_args_type[argnum] == T_REG)
		process->reg[argnum] = value;
	else if (process->op_args_type[argnum] == T_IND)
		write_data(process->op_args_pointers[argnum], value, data);
}

void	live(t_process *process, t_data *data)
{
	int		champ_num;
	t_list	*champ_p;

	champ_num = read_arg(process, 0, data) * -1;
	process->alive_cycle = data->cycle;
	champ_p = data->champs;
	while (champ_p)
	{
		if (((t_champ*)champ_p->content)->number == champ_num)
		{
			data->last_alive_champ = champ_num;
			if (data->v_1)
				ft_printf("Player %d (%s) is said to be alive\n", champ_num, ((t_champ*)champ_p->content)->name);
			return ;
		}
		champ_p = champ_p->next;
	}
}

void	st(t_process *process, t_data *data)
{
	write_arg(process, 1, read_arg(process, 0, data), data);
}

void	ld_lld(t_process *process, t_data *data)
{
	write_arg(process, 1, read_arg(process, 0, data), data);
	process->carry = (read_arg(process, 1, data) == 0);
	//dobavit` lld (ne usekat po modulu)
}

void	sub_add(t_process *process, t_data *data)
{
	if (process->op_code == 3)
		write_arg(process, 2, read_arg(process, 0, data) + read_arg(process, 1, data), data);
	else
		write_arg(process, 2, read_arg(process, 0, data) - read_arg(process, 1, data), data);
	process->carry = (read_arg(process, 2, data) == 0);
}

void	and_or_xor(t_process *process, t_data *data)
{
	if (process->op_code == 5)
		write_arg(process, 2, read_arg(process, 0, data) & read_arg(process, 1, data), data);
	else if (process->op_code == 6)
		write_arg(process, 2, read_arg(process, 0, data) | read_arg(process, 1, data), data);
	else
		write_arg(process, 2, read_arg(process, 0, data) ^ read_arg(process, 1, data), data);
	process->carry = (read_arg(process, 2, data) == 0);
}

void	zjmp(t_process *process, t_data *data)
{
	if (process->carry)
		process->position = (process->position + read_arg(process, 0, data) % IDX_MOD) % MEM_SIZE;
}

void	ldi_lldi(t_process *process, t_data *data)
{
	write_arg(process, 2, process->position + (read_arg(process, 0, data) + read_arg(process, 1, data)) % IDX_MOD, data);
}

void	sti(t_process *process, t_data *data)
{
	write_data(process->position + (read_arg(process, 1, data) + read_arg(process, 2, data)) % IDX_MOD, read_arg(process, 0, data), data);
}

void	fork_lfork(t_process *process, t_data *data)
{
	t_process new_process;

	ft_bzero(&new_process, sizeof(t_process));
	ft_memcpy(&new_process.reg, process->reg, sizeof(process->reg));
	new_process.carry = process->carry;
	new_process.alive_cycle = process->alive_cycle;
	new_process.position = (process->op_code == 12) ? (read_arg(process, 0, data) % IDX_MOD) : read_arg(process, 0, data);
	ft_lstadd(&data->processes, ft_lstnew(&new_process, sizeof(t_process)));
}

void	aff(t_process *process, t_data *data)
{
	char c;

	c = read_arg(process, 0, data);
	ft_printf("%c", c);
}

void	execute_opeartion(t_process *process, t_data *data)
{
	static void (*exec_op[17])(t_process*, t_data*);

	if (!exec_op[1])
	{
		exec_op[1] = live;
		exec_op[2] = ld_lld;
		exec_op[3] = st;
		exec_op[4] = sub_add;
		exec_op[5] = sub_add;
		exec_op[6] = and_or_xor;
		exec_op[7] = and_or_xor;
		exec_op[8] = and_or_xor;
		exec_op[9] = zjmp;
		exec_op[10] = ldi_lldi;
		exec_op[11] = sti;
		exec_op[12] = fork_lfork;
		exec_op[13] = ld_lld;
		exec_op[14] = ldi_lldi;
		exec_op[15] = fork_lfork;
		exec_op[16] = aff;
	}
	exec_op[process->op_code](process, data);
}