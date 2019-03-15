/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:46:28 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/12/04 19:40:06 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_FT_H

# define PRINTF_FT_H

# define FT_PRINTF_COLOR_RED     "\033[0;31m"
# define FT_PRINTF_COLOR_GREEN   "\033[0;32m"
# define FT_PRINTF_COLOR_YELLOW  "\033[0;33m"
# define FT_PRINTF_COLOR_BLUE    "\033[0;34m"
# define FT_PRINTF_COLOR_MAGENTA "\033[0;35m"
# define FT_PRINTF_COLOR_CYAN    "\033[0;36m"
# define FT_PRINTF_COLOR_BOLD_RED     "\033[1;31m"
# define FT_PRINTF_COLOR_BOLD_GREEN   "\033[1;32m"
# define FT_PRINTF_COLOR_BOLD_YELLOW  "\033[1;33m"
# define FT_PRINTF_COLOR_BOLD_BLUE    "\033[1;34m"
# define FT_PRINTF_COLOR_BOLD_MAGENTA "\033[1;35m"
# define FT_PRINTF_COLOR_BOLD_CYAN    "\033[1;36m"
# define FT_PRINTF_COLOR_RESET   "\033[0;0m"

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <errno.h>
# include <stddef.h>
# include "../libft/libft.h"

typedef struct				s_format {
	unsigned int			minus: 1;
	unsigned int			plus: 1;
	unsigned int			space: 1;
	unsigned int			sharp: 1;
	unsigned int			zero: 1;
	unsigned int			dollar: 1;
	unsigned int			point: 1;
	unsigned int			apostrophe: 1;
	unsigned int			specif: 4;
	unsigned int			error: 1;
	unsigned int			size;
	size_t					precision;
	size_t					width;
	unsigned int			negative:1;
	unsigned int			sign: 3;
}							t_format;

int							ft_get_format(char *str, t_format *format,
		va_list ap);
char						*ft_put_string(t_format *format, size_t *offset,
		va_list ap, char *str);
char						*ft_subprintf(char *str, size_t *bytes,
		size_t *offset, va_list ap);
int							ft_printf(const char *format, ...);
long long					ft_get_dec_value(t_format *format,
		unsigned long long num);
unsigned long long			ft_get_unsign_value(int specif,
		unsigned long long num);
char						*ft_str_add_pre_width(t_format *format,
		size_t *len, char *str);
char						*ft_add_post_width(t_format *format,
		char *str, size_t *stringlen);
char						*ft_str_add_sign(int sn, char *str,
		size_t *strlen);
char						*ft_str_add_zero(t_format *format,
		size_t *len, char *str);
char						*printf_itoa_base(unsigned long long value,
		int base, t_format *format, size_t *stringlen);
char						*ft_create_err(t_format *format, va_list ap,
		size_t *stringlen);
char						*ft_create_float(t_format *format, va_list ap,
		size_t *stringlen);
char						*ft_create_percent(t_format *format, va_list ap,
		size_t *stringlen);
char						*ft_create_chr(t_format *format, va_list ap,
		size_t *stringlen);
char						*ft_create_str(t_format *format, va_list ap,
		size_t *stringlen);
char						*ft_create_adr(t_format *format, va_list ap,
		size_t *stringlen);
char						*ft_create_dec(t_format *format, va_list ap,
		size_t *stringlen);
char						*ft_create_oct(t_format *format, va_list ap,
		size_t *stringlen);
char						*ft_create_uns(t_format *format, va_list ap,
		size_t *stringlen);
char						*ft_create_hex(t_format *format, va_list ap,
		size_t *stringlen);
char						*ft_create_wcr(unsigned long long value,
		size_t *strlen);
char						*ft_create_wsr(t_format *format, wchar_t *p,
		size_t *strlen);
char						*ft_join_spec(char c, size_t len, char *str);
char						*ft_strjoin_free_spec(char *s1, char *s2,
		size_t *oldlen, size_t *newlen);
char						*ft_strjoin_free(char *s1, char *s2);
size_t						ft_char_pos(char c, char *str);
void						ft_set_unicode(unsigned int value, char *str);
char						*ft_create_bin(t_format *format, va_list ap,
		size_t *stringlen);

int							g_errornum;

#endif
