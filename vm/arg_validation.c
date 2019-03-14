#include "vm.h"

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
				champ->number = data->pl_numbers[i] + 1;
				data->pl_numbers[i] = 1;
			}
			i++;
		}
	}
}

//void	process_dump(int argc, char** argv, int *i, t_data *data);

void	process_champ(int argc, char** argv, int *i, t_data *data)
{
	int	fd;
	t_champ *champ;

	champ = (t_champ *)malloc(sizeof(t_champ));
	fd = open(argv[*i], O_RDONLY);
	champ->name = get_champ_name(fd);
	printf("CHAMP name: %s\n", champ->name);
}

void	process_n(int argc, char** argv, int *i, t_data *data)
{
	int		n;

	*i + 1 >= argc ? error_msg("-n without number!") : 0;
	n = parse_int(argv[++(*i)]);
	n < 1 || n > MAX_PLAYERS ? error_msg("Player number less then 0 or more then MAX_PLAYERS!") : 0;
	data->next_p_num = (unsigned int)n;
}

void	arg_valid(int argc, char** argv, t_data *data)
{
	int 			i;

	i = 1;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "-n"))
			process_n(argc, argv, &i, data);
//		else if (ft_strcmp(argv[i], "-dump"))
//			process_dump(argc, argv, &i, data);
		else
			process_champ(argc, argv, &i, data);
		i++;
	}
}