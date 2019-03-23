#include "vm.h"


int main(int argc, char** argv)
{
	t_data data;
	t_list	*p;

	ft_bzero(&data, sizeof(t_data));
	reserve_numbers(argc, argv, &data);
	arg_valid(argc, argv, &data);

	ft_printf("%s\n", g_op_tab[0].name);

	introduce_champs(data.champs);

	// data.n_flag = 31;
	data.cycle = 1;
	initialization(&data);
	if (data.v_flag)
		visualize(&data);
	else
	{
		while (data.playing)
			do_turn(&data);
		p = data.champs;
		while (p && ((t_champ*)p->content)->number != data.last_alive_champ)
			p = p->next;
		ft_printf("Contestant %d, \"%s\", has won!\n", data.last_alive_champ, ((t_champ*)p->content)->name);
	}
	return (0);
}
