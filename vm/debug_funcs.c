#include "../includes/vm.h"

void	print_champ(t_champ * champ, int pr_memory)
{
	printf("CHAMPION %s [%u]\n", champ->name, champ->number);
	printf("\t\t-comment: %s\n", champ->comment);
	printf("\t\t-size: %u\n", champ->exec_size);
	printf("\t\t-header: %x\n", champ->magic_header);
	pr_memory ? ft_print_memory(champ->exec_code, champ->exec_size) : 0;
}

void	print_data(t_data *data)
{
	printf("Dump-flag = %d\n", data->dump_flag);
}