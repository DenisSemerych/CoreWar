#include "vm.h"

void	introduce_champs(t_list *champs)
{
	t_list	*tmp;
	t_champ	*champ;

	ft_printf("Introducing contestants...\n");
	tmp = champs;
	while (tmp)
	{
		champ = (t_champ *)tmp->content;
		ft_printf("* Player %u, weighing %u bytes, \"%s\" (\"%s\") !\n", champ->number, champ->exec_size, champ->name, champ->comment);
		tmp = tmp->next;
	}
}