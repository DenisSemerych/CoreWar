/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 09:03:09 by dsemeryc          #+#    #+#             */
/*   Updated: 2019/03/27 09:06:37 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void			error_function(char *msg, int *line_nbr, char *line, int check)
{
	if (line_nbr)
		ft_printf("%s Error in line #%d\n", RED, *line_nbr);
	else
		ft_printf("%sError in: ", RED);
	if (check)
		ft_printf("%s%s%s", FAIL, UNDR, line);
	else
	{
		while (*line && *line != '\n')
			ft_printf("%s%s%c", FAIL, UNDR, *line++);
	}
	ft_printf("\n");
	ft_printf(RESET);
	ft_printf(CYN);
	ft_printf(BOLD);
	ft_putendl_fd(msg, 2);
	ft_printf(RESET);
	exit(0);
}

void			print_usage(void)
{
	ft_printf("%sUSAGE: asm source_file\n%s", BOLD, RESET);
	ft_printf("Explanation: will translate your *assembler code to binary\n\n");
	ft_printf("*by assembler code we mean 42-corewar pseudo-assembler\n");
	ft_printf("%s©dsemeryc dzaporoz mmyslyvy yochered 42-Corewar-SBDK%s\n", GRN,
			RESET);
	exit(0);
}

void			check_filename(char *path)
{
	char		**splited;
	char		*name;

	splited = ft_strsplit(path, '/');
	name = ft_strdup(splited[count_size(splited) - 1]);
	free_str_arr(splited, count_size(splited));
	splited = ft_strsplit(name, '.');
	if (!ft_strequ("s", splited[count_size(splited) - 1]))
		error_function("File extension must be .s", NULL, path, 1);
	g_champ_name = ft_strdup(path);
	g_champ_name = realloc(g_champ_name, ft_strlen(path) + 2);
	ft_strcpy(g_champ_name + (ft_strlen(path) - 1), "cor");
	free_str_arr(splited, count_size(splited));
	free(name);
}

char			*read_from_file(char *file_name)
{
	int			fd;
	char		*file;
	char		buff[BUFF_SIZE + 1];
	int			rd;

	check_filename(file_name);
	if ((fd = open(file_name, O_RDONLY)) < 0)
	{
		SRC_NOT_READ(file_name);
	}
	file = ft_memalloc(1);
	if (read(fd, buff, 0) != 0)
		error_function("Error in reading", NULL, file_name, 1);
	while ((rd = read(fd, buff, BUFF_SIZE)))
	{
		buff[rd] = '\0';
		file = (char *)realloc(file, ft_strlen(file) + rd + 1);
		ft_strcat(file, buff);
	}
	return (file);
}

int				main(int argc, char **argv)
{
	char		*file;
	t_list		*arguments_list;
	int			i;

	file = NULL;
	i = 1;
	if (argc == 1)
		print_usage();
	file = read_from_file(argv[i]);
	arguments_list = tokenize(file);
	write_binary(&arguments_list);
}
