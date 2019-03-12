# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/29 14:13:02 by dsemeryc          #+#    #+#              #
#    Updated: 2019/03/11 11:11:42 by dsemeryc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

LFT_DR = ./libft

PRNTF_DR = ./ft_printf

LFT_CMP =  ft_bzero.o ft_memcpy.o ft_memccpy.o ft_memmove.o ft_memchr.o ft_memcmp.o ft_memset.o ft_strlen.o ft_strdup.o ft_strcpy.o ft_strncpy.o ft_strcat.o ft_strncat.o ft_strlcat.o ft_strchr.o ft_strrchr.o ft_strstr.o ft_strnstr.o ft_strcmp.o ft_strncmp.o ft_atoi.o  ft_isalpha.o ft_isdigit.o ft_isalnum.o ft_isascii.o ft_isprint.o ft_toupper.o ft_tolower.o ft_memalloc.o ft_memdel.o ft_strnew.o ft_strdel.o ft_strclr.o ft_striter.o ft_striteri.o ft_strmap.o ft_strmapi.o ft_strequ.o ft_strnequ.o ft_strsub.o ft_strjoin.o ft_strtrim.o ft_strsplit.o ft_itoa.o ft_putchar.o ft_putstr.o ft_putendl.o ft_putnbr.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o ft_lstnew.o ft_lstdelone.o ft_lstdel.o ft_lstadd.o ft_lstiter.o ft_lstmap.o ft_print_memory.o ft_print_bits.o ft_reversebits.o ft_insertion.o ft_pow.o get_next_line.o

PRNTF_CMP = formating.o formating_2.o ft_itoa_int128.o ft_printf.o itoa_base_long.o itoa_base_ull.o print_float.o print_float_add.o print_int.o add_func.o stack_func.o stack_func_2.o service_functions.o service_functions2.o

INCLUDES_DR = ./includes

CMPLD = $(LFT_CMP) $(PRNTF_CMP)

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(LFT_CMP): %.o: $(LFT_DR)/%.c
	@gcc -c $(CFLAGS) -I $(INCLUDES_DR) $< -o $@

$(PRNFT_CMP): %.o: $(PRNFT_DR)/%.c
	@gcc -c $(CFLAGS) -I $(INCLUDES_DR) $< -o $@

$(NAME): $(CMPLD)
	@ar rc $(NAME) $(CMPLD)
	@ranlib $(NAME)
	@echo $(NAME) "Beta-version Printf(ugly) created"

clean:
	@rm -f $(CMPLD)
	@echo "cleaned *.o files"

fclean: clean
	@rm -f $(NAME) $(LFT_DR)/libft.a
	echo "deleted" $(NAME)

re: fclean all
