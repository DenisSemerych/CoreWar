#include "vm.h"

unsigned int	process_n(int argc, char** argv, int *i, t_data *data)
{
	int		n;

	*i + 1 >= argc ? error_msg("-n without number!") : 0;
	n = parse_int(argv[++(*i)]);
	n < 1 || n > MAX_PLAYERS ? error_msg("Player number less then 0 or more then MAX_PLAYERS!") : 0;
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
			n = process_n(argc, argv, &i, data);
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

//void	process_dump(int argc, char** argv, int *i, t_data *data);

void	process_champ(int argc, char** argv, int *i, t_data *data)
{
	int	fd;
	t_champ *champ;
	t_list	*tmp;

	champ = (t_champ *)malloc(sizeof(t_champ));
	fd = open(argv[*i], O_RDONLY);
	champ->magic_header = get_champ_4_bytes(fd);
	champ->magic_header != 0xEA83F3 ? error_msg("Champion have false magic header!") : 0;
	champ->name = get_champ_name(fd);
	get_champ_4_bytes(fd) != 0 ? error_msg("Null zones isn't nulled!") : 0;
	champ->exec_size = get_champ_4_bytes(fd);
	champ->exec_size > CHAMP_MAX_SIZE ? error_msg("Size of champion larger then CHAMP_MAX_SIZE!") : 0;
	champ->comment = ft_strdup(get_champ_comment(fd));
	get_champ_4_bytes(fd) != 0 ? error_msg("Null zones isn't nulled!") : 0;
	champ->exec_code = get_champ_exec(fd, champ->exec_size);
	set_champ_num(data, champ);
	tmp = ft_lstnew(0, 0);
	tmp->content = champ;
	ft_lstadd(&(data->champs), tmp);
}

void	arg_valid(int argc, char** argv, t_data *data)
{
	int 			i;

	i = 1;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "-n") == 0)
			data->next_p_num = process_n(argc, argv, &i, data);
//		else if (ft_strcmp(argv[i], "-dump"))
//			process_dump(argc, argv, &i, data);
		else
			process_champ(argc, argv, &i, data);
		i++;
	}
}