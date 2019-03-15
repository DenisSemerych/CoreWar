#include "vm.h"

int main(int argc, char** argv)
{
	t_data data;

	int i = 1;
	ft_bzero(&data, sizeof(t_data));
	reserve_numbers(argc, argv, &data);
	arg_valid(argc, argv, &data);
	t_list *tmp = data.champs;
	print_data(&data);
	while (tmp)
	{
		print_champ((t_champ *)(tmp->content), 0);
		tmp = tmp->next;
	}
	return (0);
}