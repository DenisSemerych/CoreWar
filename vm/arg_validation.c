/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmyslyvy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 00:07:49 by mmyslyvy          #+#    #+#             */
/*   Updated: 2019/03/26 00:23:16 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

unsigned int	fl_process(int argc, char **argv, int *i, int op)
{
	int	n;

	*i + 1 >= argc ? error_msg("Flag without number!") : 0;
	n = parse_int(argv[++(*i)]);
	op == 1 && (n < 1 || n > MAX_PLAYERS) ?
		error_msg("Player number less then 0 or more then MAX_PLAYERS!") : 0;
	op == 2 && n < 0 ? error_msg("Num of cycles can't be negative or 0!") : 0;
	op == 3 && (n < 0 || n > 31) ? error_msg("Invalid num after -v flag") : 0;
	return ((unsigned int)n);
}

void			reserve_numbers(int argc, char **argv, t_data *data)
{
	int i;
	int n;

	i = 1;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "-n") == 0)
		{
			n = fl_process(argc, argv, &i, 1);
			data->pl_numbers[n - 1] == 2 ?
				error_msg("There can not be players with same numbers!") : 0;
			data->pl_numbers[n - 1] = 2;
		}
		i++;
	}
}

void			set_champ_num(t_data *data, t_champ *champ)
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
		champ->number == 0 ?
			error_msg("There are more champs, then MAX_PLAYERS!") : 0;
	}
}

void			process_champ(char **argv, int *i, t_data *data)
{
	int		fd;
	char	*ext;
	t_champ	*champ;

	champ = (t_champ *)malloc(sizeof(t_champ));
	if (!(ext = ft_strrchr(argv[*i], '.')) || !ft_strequ(ext, ".cor"))
		error_msg("File doesn't have extension .cor");
	if ((fd = open(argv[*i], O_RDONLY)) == -1)
		error_msg("Cannot open a file");
	champ->magic_header = get_champ_4_bytes(fd);
	champ->magic_header != COREWAR_EXEC_MAGIC ?
		error_msg("Champion have false magic header!") : 0;
	champ->name = get_champ_name(fd);
	get_champ_4_bytes(fd) != 0 ? error_msg("Null zones isn't nulled!") : 0;
	champ->exec_size = get_champ_4_bytes(fd);
	champ->exec_size > CHAMP_MAX_SIZE ?
		error_msg("Size of champion larger then CHAMP_MAX_SIZE!") : 0;
	champ->comment = get_champ_comment(fd);
	get_champ_4_bytes(fd) != 0 ? error_msg("Null zones isn't nulled!") : 0;
	champ->exec_code = get_champ_exec(fd, champ->exec_size);
	set_champ_num(data, champ);
	data->last_alive_champ = champ->number;
	insert_champ(data, champ);
	data->champs_amount++;
	close(fd);
}

void			arg_valid(int argc, char **argv, t_data *data)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "-n") == 0)
			data->next_p_num = fl_process(argc, argv, &i, 1);
		else if (ft_strcmp(argv[i], "-dump") == 0)
		{
			data->dump_flag = 1;
			data->dump_cycles = fl_process(argc, argv, &i, 2);
		}
		else if (ft_strcmp(argv[i], "-visual") == 0)
			data->visual_flag = 1;
		else if (ft_strcmp(argv[i], "-v") == 0)
			data->n_flag = fl_process(argc, argv, &i, 3);
		else if (ft_strcmp(argv[i], "-a") == 0)
			data->a_flag = 1;
		else
			process_champ(argv, &i, data);
		i++;
	}
}
