#include "vm.h"

int main(int argc, char** argv)
{
	t_data data;

	ft_bzero(&data, sizeof(t_data));
	reserve_numbers(argc, argv, &data);
	arg_valid(argc, argv, &data);

	ft_printf("%s\n", g_op_tab[0].name);

	introduce_champs(data.champs);


//	data.v_1 = 1;
//	data.v_0 = 1;
//	data.v_2 = 1;
	data.v_4 = 1;
//	data.v_16 = 1;
	initialization(&data);
	while (data.playing)
		do_turn(&data);
	return (0);
}
