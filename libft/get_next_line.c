/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 16:56:53 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/11/01 17:47:25 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*find_list(int fd, t_list **remnant)
{
	t_list	*temp;

	if (!(*remnant))
	{
		*remnant = ft_lstnew(NULL, 0);
		(*remnant)->content_size = fd;
		(*remnant)->content = (void*)ft_strnew(1);
		return (*remnant);
	}
	temp = *remnant;
	while ((int)temp->content_size != fd && temp->next != NULL)
		temp = temp->next;
	if ((int)temp->content_size == fd)
		return (temp);
	temp->next = ft_lstnew(NULL, 0);
	temp->next->content_size = fd;
	temp->next->content = (void*)ft_strnew(1);
	return (temp->next);
}

static int		fill_buff(int fd, t_list **remnant)
{
	char		*temp;
	char		buf[BUFF_SIZE + 1];
	int			rb;
	t_list		*p;

	rb = 1;
	if (fd < 0 || BUFF_SIZE < 1 || read(fd, 0, 0))
		return (-1);
	if (!(p = find_list(fd, remnant)))
		return (-1);
	if (p->content == NULL)
		p->content = ft_strnew(1);
	while (!ft_strchr((char*)p->content, '\n') &&
			(rb = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[rb] = '\0';
		temp = ft_strjoin((char*)p->content, buf);
		free(p->content);
		p->content = (char*)temp;
	}
	if (rb < 0)
		free(p->content);
	return (rb);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*remnant;
	t_list			*p;
	char			*temp;
	int				rb;

	p = find_list(fd, &remnant);
	if (!line || (rb = fill_buff(fd, &remnant)) < 0 || !p)
		return (-1);
	if (!ft_strlen((char*)p->content))
		return (0);
	temp = NULL;
	if (!ft_strchr(p->content, '\n'))
		*line = ft_strdup(p->content);
	else
	{
		*line = ft_strsub((char*)p->content, 0, ft_strchr((char*)p->content,
					'\n') - (char*)p->content);
		temp = ft_strsub((char*)p->content, ft_strchr((char*)p->content,
					'\n') - (char*)p->content + 1,
				ft_strlen((char*)p->content));
	}
	free(p->content);
	p->content = temp;
	return (1);
}
