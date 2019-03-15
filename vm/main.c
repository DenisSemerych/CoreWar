#include "vm.h"

void	process_champ(int argc, char** argv, int *i, t_data *data);

int main(int argc, char** argv)
{
	t_data data;

	int i = 1;
	ft_bzero(&data, sizeof(t_data));
	process_champ(argc, argv, &i, &data);
//	ft_putstr("test");
	return (0);
}