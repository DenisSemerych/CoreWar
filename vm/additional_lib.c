#include "vm.h"

void	error_msg(char *str)
{
	ft_putstr("Error: ");
	ft_putendl(str);
	exit(1);
}

int		parse_int(char *str)
{
	int		num;
	char	*tstr;

	num = ft_atoi(str);
	tstr = ft_itoa(num);
	if (ft_strcmp(str, tstr) != 0)
	{
		free(tstr);
		error_msg("Bad integer value");
		return (0);
	}
	else
	{
		free(tstr);
		return (num);
	}
}