#include "vm.h"

int main(int argc, char** argv)
{
	t_data data;

	ft_bzero(&data, sizeof(t_data));
	reserve_numbers(argc, argv, &data);
	arg_valid(argc, argv, &data);

	introduce_champs(data.champs);

	initialization(&data);
	while (data.playing)
		do_turn(&data);
	return (0);
}
