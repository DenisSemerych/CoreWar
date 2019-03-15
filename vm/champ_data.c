#include "vm.h"

unsigned int	*get_champ_4_bytes(int fd)
{
	unsigned char bytes[4];
	unsigned int res;

	read(fd, &bytes, 4);
	res = (unsigned int)bytes[0] << 24;
	res = res | ((unsigned int)bytes[1] << 16);
	res = res | ((unsigned int)bytes[2] << 8);
	res = res | (unsigned int)bytes[3];
	return (res);
}

char	*get_champ_name(int fd)
{
	char	name[PROG_NAME_LENGTH + 1];

	read(fd, &name, PROG_NAME_LENGTH);
	name[PROG_NAME_LENGTH + 1] = 0;
	return (ft_strdup(name));
}

char	*get_champ_comment(int fd)
{
	char	comment[COMMENT_LENGTH + 1];

	read(fd, &comment, COMMENT_LENGTH);
	comment[COMMENT_LENGTH + 1] = 0;
	return (ft_strdup(comment));
}

unsigned char	*get_champ_exec(int fd, int code_size)
{
	unsigned char	code[CHAMP_MAX_SIZE];
	unsigned char	*tmp;
	int				i;

	i = -1;
	tmp = (unsigned char *)malloc(sizeof(unsigned char) * code_size);
	read(fd, &code, code_size);
	while (++i < code_size)
		tmp[i]= code[i];
	return (tmp);
}