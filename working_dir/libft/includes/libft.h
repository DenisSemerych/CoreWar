/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 15:50:47 by dsemeryc          #+#    #+#             */
/*   Updated: 2019/03/10 14:10:19 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# define BUFF_SIZE 1

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;
typedef struct		s_coord
{
	int				x;
	int				y;
	struct s_coord	*next;
}					t_coord;
typedef	struct		s_stack
{
	int				data;
	struct s_stack	*next;
}					t_stack;
int					str_arr_count(char **arr);
void				free_str_arr(char **arr, int size);
int					stack_size(t_stack *stack);
t_stack				*find_max(t_stack *to_find);
void				push(t_stack **stack_one, t_stack **stack_two);
t_stack				*find_last(t_stack *head);
void				swap(t_stack **stack_a, t_stack **stack_b);
void				rotate(t_stack **head, t_stack **head_b);
void				rev_rotate(t_stack **head, t_stack **head_b);
t_stack				*create_stack(int *data, int size);
void				free_list(t_stack **stack);
void				is_sorted(t_stack *stack);
void				free_lst(t_coord **coord);
void				free_str_arr(char **arr, int size);
void				add_new(t_coord **coord, t_coord *elem);
t_coord				*initialize_coord(int x, int y);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *str);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
void				*ft_memalloc(size_t size);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strchr(const char *s, int c);
char				*ft_strnchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				**ft_strsplit(char const *s, char c);
int					ft_isdigit(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
char				*ft_itoa(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void	const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *newl);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_print_bits(unsigned char octet);
unsigned char		ft_reversed_bits(unsigned char octet);
void				ft_print_memory(const void *addr, size_t size);
int					*ft_insertion(int *arr, int	size);
int					get_next_line(const int fd, char **line);
int					ft_pow(int num, int power);
void				ft_lstaddend(t_list **alst, t_list **new);
int					get_next_line(const int fd, char **line);
int					count_size(char **arr);
t_stack				*find_before_last(t_stack *head);
void				put_err_msg_exit(char *str);
#endif
