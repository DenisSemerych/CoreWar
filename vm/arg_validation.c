#include "vm.h"

void	process_dump(int argc, char** argv, int *i, unsigned int *pl_numbers);
void	process_champ(int argc, char** argv, int *i, unsigned int *pl_numbers);

void	process_n(int argc, char** argv, int *i, unsigned int *pl_numbers);

void	arg_valid(int argc, char** argv)
{
	unsigned int	pl_numbers[MAX_PLAYERS];
	int 			i;

	i = 1;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "-n"))
			process_n(argc, argv, &i, &pl_numbers);
		else if (ft_strcmp(argv[i], "-dump"))
			process_dump(argc, argv, &i, &pl_numbers);
		else
			process_champ(argc, argv, &i, &pl_numbers);
	}
}