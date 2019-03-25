#include "../includes/vm.h"


int main(int argc, char **argv)
{
	t_data	data;
	t_list	*p;

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
		p = data.champs;
		while (p && ((t_champ*)p->content)->number != data.last_alive_champ)
			p = p->next;
		ft_printf("Contestant %d, \"%s\", has won !\n", data.last_alive_champ, ((t_champ*)p->content)->name);
	}
	system("leaks -q corewar");
	return (0);
}
