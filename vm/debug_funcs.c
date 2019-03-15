#include "vm.h"

void	print_champ(t_champ * champ)
{
	printf("CHAMPION %s [%u]\n", champ->name, champ->number);
	printf("\t\t-comment: %s\n", champ->comment);
	printf("\t\t-size: %u\n", champ->exec_size);
	printf("\t\t-header: %x\n", champ->magic_header);
	ft_print_memory(champ->exec_code, champ->exec_size);
}