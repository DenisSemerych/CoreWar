#include "vm.h"
#include "visu.h"

int main(int argc, char** argv)
{
	t_data data;

	ft_bzero(&data, sizeof(t_data));
	visualize(&data);
	// reserve_numbers(argc, argv, &data);
	// arg_valid(argc, argv, &data);

	// ft_printf("%s\n", g_op_tab[0].name);

	// introduce_champs(data.champs);

	// unsigned char test[3];
	// test = codage_proc(0x90);
	// initialization(&data);
	// while (data.playing)
	// 	do_turn(&data);
	return (0);
}
