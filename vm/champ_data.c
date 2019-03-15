#include "vm.h"

char	*get_champ_name(int fd)
{
	char	name[PROG_NAME_LENGTH + 1];

	lseek(fd, 4, SEEK_SET);
	read(fd, &name, PROG_NAME_LENGTH);
	name[PROG_NAME_LENGTH + 1] = 0;
	return (name);
}

char	*get_champ_comment(int fd);

char	*get_champ_code(int fd);