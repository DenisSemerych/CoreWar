# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/23 14:56:42 by dzaporoz          #+#    #+#              #
#    Updated: 2019/03/15 13:32:22 by dzaporoz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

FLAGS =	-Wall -Wextra -Werror -O2

LFT_DIR = ./

PRFT_DIR = ./ftprintf

LFT_HDR = $(LFT_DIR)libft.h

PRFT_HRD = $(PRFT_DIR)ft.h

LFT_COMPILED =	ft_bzero.o ft_memcpy.o ft_memccpy.o ft_memmove.o ft_memchr.o ft_memcmp.o ft_memset.o ft_strlen.o ft_strdup.o ft_strcpy.o ft_strncpy.o ft_strcat.o ft_strncat.o ft_strlcat.o ft_strchr.o ft_strrchr.o ft_strstr.o ft_strnstr.o ft_strcmp.o ft_strncmp.o ft_atoi.o ft_itoa_chk.o ft_isalpha.o ft_isdigit.o ft_isalnum.o ft_isascii.o ft_isprint.o ft_toupper.o ft_tolower.o ft_memalloc.o ft_memdel.o ft_strnew.o ft_strdel.o ft_strclr.o ft_striter.o ft_striteri.o ft_strmap.o ft_strmapi.o ft_strequ.o ft_strnequ.o ft_strsub.o ft_strjoin.o ft_strtrim.o ft_strsplit.o ft_splitdel.o ft_itoa.o ft_putchar.o ft_putstr.o ft_putendl.o ft_putnbr.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o ft_lstnew.o ft_lstdelone.o ft_lstdel.o ft_lstadd.o ft_lstiter.o ft_lstmap.o ft_lstcount.o ft_atoi_base.o ft_itoa_base.o ft_print_memory.o ft_strrev.o ft_sort_int_tab.o ft_count_words.o ft_isspace.o ft_lstcontdel.o get_next_line.o

PRFT_COMPILED =	auxiliary.o chars_and_strings.o flags_reading.o formating.o ft_printf.o ft_puts.o print_num.o create_float.o

COMPILED = $(LFT_COMPILED) $(PRFT_COMPILED)

all: $(NAME)

$(LFT_COMPILED): %.o: $(LFT_DIR)/%.c
	@gcc -c $(FLAGS) -I $(LFT_DIR) $< -o $@

$(PRFT_COMPILED): %.o: $(PRFT_DIR)/%.c
	@gcc -c $(FLAGS) -I $(LFT_DIR) -I $(PRFT_DIR) $< -o $@

$(NAME): $(COMPILED)
	@ar rc $(NAME) $(COMPILED)
	@ranlib $(NAME)

clean:
	@rm -f $(COMPILED)

fclean: clean
	@rm -f $(NAME)

re: fclean all

