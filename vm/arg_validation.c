#include "vm.h"

unsigned int	fl_process(int argc, char** argv, int *i, int op)
{
	int	n;

	*i + 1 >= argc ? error_msg("Flag without number!") : 0;
	n = parse_int(argv[++(*i)]);
	op == 1 && (n < 1 || n > MAX_PLAYERS) ? error_msg("Player number less then 0 or more then MAX_PLAYERS!") : 0;
	op == 2 && n <= 0 ? error_msg("Number of cycles cannot be negative or zero!") : 0;
	return ((unsigned int)n);
}

void	reserve_numbers(int argc, char **argv, t_data *data)
{
	int i;
	int n;

	i = 1;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "-n") == 0)
		{
			n = fl_process(argc, argv, &i, 1);
			data->pl_numbers[n - 1] == 2 ? error_msg("There can not be players with same numbers!") : 0;
			data->pl_numbers[n - 1] = 2;
		}
		i++;
	}
}

void	set_champ_num(t_data *data, t_champ *champ)
{
	int i;

	i = 0;
	if (data->next_p_num)
	{
		champ->number = data->next_p_num;
		data->next_p_num = 0;
	}
	else
	{
		while (i < MAX_PLAYERS)
		{
			if (!data->pl_numbers[i])
			{
				champ->number = i + 1;
				data->pl_numbers[i] = 1;
				break ;
			}
			i++;
		}
		champ->number == 0 ? error_msg("There are more champions, then MAX_PLAYERS!") : 0;
	}
}

void	insert_champ(t_data *data, t_champ *champ)
{
	t_list	*new_lst;
	t_list	*tmp;
	t_list	*prev_next;

	new_lst = ft_lstnew(0, 0);
	new_lst->content = champ;
	if (data->champs == NULL)
	{
		ft_lstadd(&(data->champs), new_lst);
		return ;
	}
	else if (data->champs->next == NULL)
	{
		if (((t_champ *)(data->champs->content))->number > champ->number)
			ft_lstadd(&(data->champs), new_lst);
		else
			data->champs->next = new_lst;
		return ;
	}
	tmp = data->champs;
	while (tmp->next && ((t_champ *)(tmp->next->content))->number < champ->number)
		tmp = tmp->next;
	prev_next = tmp->next;
	tmp->next = new_lst;
	new_lst->next = prev_next;
}

void	process_champ(int argc, char** argv, int *i, t_data *data)
{
	int	fd;
	t_champ *champ;
	t_list	*tmp;

	champ = (t_champ *)malloc(sizeof(t_champ));
	fd = open(argv[*i], O_RDONLY);
	champ->magic_header = get_champ_4_bytes(fd);
	champ->magic_header != COREWAR_EXEC_MAGIC ? error_msg("Champion have false magic header!") : 0;
	champ->name = get_champ_name(fd);
	get_champ_4_bytes(fd) != 0 ? error_msg("Null zones isn't nulled!") : 0;
	champ->exec_size = get_champ_4_bytes(fd);
	champ->exec_size > CHAMP_MAX_SIZE ? error_msg("Size of champion larger then CHAMP_MAX_SIZE!") : 0;
	champ->comment = ft_strdup(get_champ_comment(fd));
	get_champ_4_bytes(fd) != 0 ? error_msg("Null zones isn't nulled!") : 0;
	champ->exec_code = get_champ_exec(fd, champ->exec_size);
	set_champ_num(data, champ);
//	tmp = ft_lstnew(0, 0);
//	tmp->content = champ;
//	ft_lstadd(&(data->champs), tmp);
	insert_champ(data, champ);
	data->champs_amount++;
}

void	arg_valid(int argc, char** argv, t_data *data)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "-n") == 0)
			data->next_p_num = fl_process(argc, argv, &i, 1);
		else if (ft_strcmp(argv[i], "-dump") == 0)
			data->dump_flag = fl_process(argc, argv, &i, 2);
		else if (ft_strcmp(argv[i], "-v") == 0)
			data->v_flag = 1;
		else
			process_champ(argc, argv, &i, data);
		i++;
	}
}