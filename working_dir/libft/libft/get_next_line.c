/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 20:55:13 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/11/08 18:12:58 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void				give_line(t_list **lst, char **line)
{
	char			*file;
	char			*str_left;
	t_list			*tmp;

	tmp = *lst;
	if (tmp->content && line)
	{
		if ((file = ft_strchr(tmp->content, '\n')))
		{
			*line = ft_strsub((char *)tmp->content, 0,
					file - (char *)tmp->content);
			str_left = ft_strdup((char *)file + 1);
			free(tmp->content);
			tmp->content = str_left;
		}
		else
		{
			*line = ft_strsub(tmp->content, 0, ft_strlen(tmp->content));
			free(tmp->content);
			tmp->content = NULL;
		}
	}
}

t_list				*look_at_list(t_list **lst, int fd)
{
	t_list			*crawler;
	t_list			*tmp;

	crawler = *lst;
	while (crawler && crawler->content)
	{
		if ((int)crawler->content_size == fd)
		{
			tmp = crawler;
			return (tmp);
		}
		crawler = crawler->next;
	}
	tmp = ft_lstnew(NULL, 0);
	tmp->content = ft_strnew(1);
	tmp->content_size = fd;
	ft_lstadd(lst, tmp);
	return (tmp);
}

int					get_next_line(const int fd, char **line)
{
	static t_list	*lst;
	t_list			*with_fd;
	char			buff[BUFF_SIZE + 1];
	char			*tmp;
	int				rd;

	if (fd < 0 || (rd = read(fd, buff, 0) != 0) || BUFF_SIZE < 1)
		return (-1);
	with_fd = look_at_list(&lst, fd);
	while ((rd = read(fd, buff, BUFF_SIZE)))
	{
		buff[rd] = '\0';
		tmp = ft_strjoin(with_fd->content, buff);
		free(with_fd->content);
		with_fd->content = tmp;
		if (ft_strchr(with_fd->content, '\n'))
			break ;
	}
	if (rd < BUFF_SIZE && !ft_strlen(with_fd->content))
		return (0);
	give_line(&with_fd, line);
	return (1);
}
