/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 19:15:08 by dsemeryc          #+#    #+#             */
/*   Updated: 2018/12/09 16:11:55 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_PRINTF_H
# define PRINTF_PRINTF_H
# include <stdarg.h>
# include "libft.h"
# define IS_FLAG(c) (c == '#' || c == '+' || c == '-' || c == ' ' || c == '0')
# define IS_TYPEFLAG(c) (c == 'l' || c == 'h' || c == 'j' || T2(c))
# define T2(c) (c == 'z' || c == 'L')
# define IS_TYPESPECIFIER(c) (B(c) || A(c) || E(c))
# define B(c) (c == 'c' || c == 'f' || c == 'd' || c == 'i' || c == 'o')
# define A(c) (c == 'x' || c == 'X' || c == 's' || c == 'u')
# define E(c) (c == 'p' || c == 'U' || c == 'D' || c == 'O' || c == 'F')
# define IS_INTCONVERT(c) (C(c) || D(c))
# define C(c) (c == 'd' || c == 'i' || c == 'u' || c == 'c' || c == 'o')
# define D(c) (c == 'x' || c == 'X' || c == 'U' || c == 'D' || c == 'O')
# define IS_ZERO_PER(num, prercision) (num == 0 && prercision == 0 ? 1 : 0)
# define NO_SIGN(c) (c == 'o' || c == 'O' || c == 'c' || c == 'p' || A (c))
# define MAG   "\x1B[35m"
# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define CYN   "\x1B[36m"
# define RESET "\x1B[0m"

int			ft_printf(const char *format, ...);
char		*ibull(unsigned long long int num, int base, int per);
char		*ibl(long long int num, int base, int *sign, int per);
char		*ft_itoa_uint128(__uint128_t num);
void		make_int_cnv(char **str, int *arr, char c);
int			is_zero_percision(int num, int prercision);
int			formate(char *str, int *arr, char p, int sign);
int			print_float(long double num, int *arr, char c);
int			print_pointer(void *pointer, int *arr);
int			print_int(void *num, char c, int *arr, int sign);
int			print_char(char ch, int *arr);
void		set_to_zero(int *arr);
void		str_to_upper(char **str);
int			no_numbers(char *str);
void		extra_sign(char **str, int *arr, int sign);
int			make_number(char **format);
void		octocorp(char **str, int *arr, char c, char *tmp);
void		look_for_add_sym(char **str, int *arr, char p, int sign);
int			all_zeroes(char *str);
void		add_zeros(char **str, int percision, int i);
int			give_index(char *str, int percision);
int			is_nan_or_inf(char **tmp, long double num, int *arr);
int			get_sign(double num);
#endif
