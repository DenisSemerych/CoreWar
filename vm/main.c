#include "vm.h"

void	process_champ(int argc, char** argv, int *i, t_data *data);

int main(int argc, char** argv)
{
	t_data data;

	int i = 0;
	ft_bzero(&data, sizeof(t_data));
	process_champ(argc, argv, &i, &data);
	initialization(&data);
	while (data.playing)
		do_turn(&data);
	return (0);
}