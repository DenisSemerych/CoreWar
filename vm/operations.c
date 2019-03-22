#include "vm.h"

void	write_data(void *position, int value, t_data *data)
{
	int n;
	unsigned char *p;

	n = 0;
	p = position;
	while (n < 4)
	{
		*p++ = (value & 0xFF000000) >> 24;
		value <<= 8;
		if (p - data->board > MEM_SIZE)
			p = data->board;
		n++;
	}
}

int 	read_arg(t_process *process, int argnum, t_data *data, int dir_flag)
{
	int arg;
	int size;
	int n;
	unsigned char *p;

	n = 0;
	arg = 0;
	p = process->op_args_pointers[argnum];
	size = get_type_size(process, process->op_args_type[argnum]);
	if (dir_flag == INDIRECT && process->op_args_type[argnum] == T_IND)
	{
		size = 4;
		p = get_t_ind_pointer(data, process, argnum);
	}
	while (n < size)
	{
		arg <<= 8;
		arg |= (int)*p++;
		if (p - data->board > MEM_SIZE)
			p = data->board;
		n++;
	}
	arg = (size == 2) ? (short)arg : arg;
	arg = ((dir_flag == INDIRECT && process->op_args_type[argnum] == T_REG) ? process->reg[arg] : arg);
	return (arg);
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

	champ_num = read_arg(process, 0, data, INDIRECT);
	process->alive_cycle = data->cycle;
	data->live_op_amount++;
	champ_p = data->champs;
	if (data->n_flag & 4)
		ft_printf("P%5d | live %d\n", process->uniq_number, champ_num);
	champ_num *= -1;
	while (champ_p)
	{
		if (((t_champ*)champ_p->content)->number == champ_num)
		{
			data->last_alive_champ = champ_num;
			if (data->n_flag & 1)
				ft_printf("Player %d (%s) is said to be alive\n", champ_num, ((t_champ*)champ_p->content)->name);
			return ;
		}
		champ_p = champ_p->next;
	}
}

void	st(t_process *process, t_data *data)
{
	int what;
	int from;
	int where;

	what = read_arg(process, 0, data, INDIRECT);
	from = read_arg(process, 0, data, DIRECT);
	where = read_arg(process, 1, data, DIRECT);

	if (process->op_args_type[1] == T_REG)
		process->reg[where] = what;
	else
		write_data(get_t_ind_pointer(data, process, 1), what, data);
	if (data->n_flag & 4)
		ft_printf("P%5d | st r%d %s%d\n", process->uniq_number, from, (process->op_args_type[1] == T_REG) ? "r" : "", where);
}

void	ld_lld(t_process *process, t_data *data)
{
	int value;
	int ind;

	value = read_arg(process, 0, data, INDIRECT);
	ind = read_arg(process, 1, data, DIRECT);


	process->carry = ((process->reg[ind] = value) == 0);
	if (data->n_flag & 4)
		ft_printf("P%5d | %s %d r%d\n", process->uniq_number, (process->op_code == 2) ? "ld" : "lld", value, ind);
}

void	sub_add(t_process *process, t_data *data)
{
	if (process->op_code == 3)
		write_arg(process, 2, read_arg(process, 0, data, INDIRECT) +
				read_arg(process, 1, data, INDIRECT), data);
	else
		write_arg(process, 2, read_arg(process, 0, data, INDIRECT) -
				read_arg(process, 1, data, INDIRECT), data);
	process->carry = (read_arg(process, 2, data, INDIRECT) == 0);
}

void	and_or_xor(t_process *process, t_data *data)
{
	if (process->op_code == 5)
		write_arg(process, 2, read_arg(process, 0, data, INDIRECT) &
				read_arg(process, 1, data, INDIRECT), data);
	else if (process->op_code == 6)
		write_arg(process, 2, read_arg(process, 0, data, INDIRECT) |
				read_arg(process, 1, data, INDIRECT), data);
	else
		write_arg(process, 2, read_arg(process, 0, data, INDIRECT) ^
				read_arg(process, 1, data, INDIRECT), data);
	process->carry = (read_arg(process, 2, data, INDIRECT) == 0);
}

void	zjmp(t_process *process, t_data *data)
{
	int value;

	value = read_arg(process, 0, data, INDIRECT) % IDX_MOD;
	if (process->carry)
		process->position = get_absolute_cord (process->position, value);
	if (data->n_flag & 4)
		ft_printf("P%5d | zjmp %d %s\n", process->uniq_number, value, (process->carry) ? "OK" : "FAIL");
}

void	ldi_lldi(t_process *process, t_data *data)
{
	write_arg(process, 2, process->position + (read_arg(process, 0, data, INDIRECT) +
			read_arg(process, 1, data, INDIRECT)) % IDX_MOD, data);
}

void	sti(t_process *process, t_data *data)
{
	int sum;
	int from;
	int pos1;
	int pos2;
	int mod;

	from = read_arg(process, 0, data, DIRECT);
	pos1 = read_arg(process, 1, data, INDIRECT);
	pos2 = read_arg(process, 2, data, INDIRECT);
	sum = pos1 + pos2;
	mod = sum % IDX_MOD + process->position;

	if (data->n_flag & 4)
		ft_printf("P%5d | sti r%d %d %d\n       | -> store to %d + %d = %d (with pc and mod %d)\n", process->uniq_number, from, pos1, pos2, pos1, pos2, sum, mod);

	write_data(&data->board[get_absolute_cord(process->position, sum)], read_arg(process, 0, data, INDIRECT), data);
}

void	fork_lfork(t_process *process, t_data *data)
{
	t_process	new_process;
	int 		value;

	value = read_arg(process, 0, data, INDIRECT);
	value = (process->op_code == 12) ? (value % IDX_MOD) : value;
	ft_bzero(&new_process, sizeof(t_process));
	ft_memcpy(&new_process.reg, process->reg, sizeof(process->reg));
	new_process.uniq_number = ++data->max_process_num;
	new_process.carry = process->carry;
	new_process.alive_cycle = process->alive_cycle;
	new_process.position = process->position + value;
	new_process.live = 1;
	ft_lstadd(&data->processes, ft_lstnew(&new_process, sizeof(t_process)));
	if (data->n_flag & 4)
		ft_printf("P%5d | %s %d (%d)\n", process->uniq_number, (process->op_code == 12) ? "fork" : "lfork", value, new_process.position);

}

void	aff(t_process *process, t_data *data)
{
	char c;

	c = read_arg(process, 0, data, INDIRECT);
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