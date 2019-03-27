/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochered <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 23:39:43 by yochered          #+#    #+#             */
/*   Updated: 2019/03/25 23:39:45 by yochered         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	print_champ(t_data *data)
{
	t_list *p;

	p = data->champs;
	while (p && ((t_champ*)p->content)->number
		!= (unsigned int)data->last_alive_champ)
		p = p->next;
	ft_printf("Contestant %d, \"%s\", has won !\n",
		data->last_alive_champ, ((t_champ*)p->content)->name);
}

int		main(int argc, char **argv)
{
	t_data	data;

	if (argc == 1)
	{
		ft_printf("\x1b[0;36mUsage: ./corewar"
				"[-a -visual -dump N -v N -n N]\n\x1b[0m");
		exit(0);
	}
	ft_bzero(&data, sizeof(t_data));
	reserve_numbers(argc, argv, &data);
	arg_valid(argc, argv, &data);
	introduce_champs(data.champs);
	data.cycle = 1;
	data.cycles_fr_lst_check = 1;
	initialization(&data);
	if (data.visual_flag)
		visualize(&data);
	else
	{
		while (data.playing)
			do_turn(&data);
		print_champ(&data);
	}
	return (0);
}
