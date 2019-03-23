# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yochered <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/18 10:41:22 by yochered          #+#    #+#              #
#    Updated: 2019/03/18 10:41:24 by yochered         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

VM_SRCDIR = vm/
VM_SRC_LIST = \
	main.c\
	additional_lib.c\
	arg_validation.c\
	champ_data.c\
	codage.c\
	debug_funcs.c\
	do_turn.c\
	initialization.c\
	intro_champs.c\
	op.c\
	operations.c\
	print_board.c

VISU_SRCDIR = $(VM_SRCDIR)visu/
VISU_SRC_LIST = \
	visu.c\
	window_funcs.c\
	draw_board.c\
	draw_info.c\
	init.c
VISU_SRC = $(addprefix $(VISU_SRCDIR), $(VISU_SRC_LIST))

OBJDIR = ./obj/
VM_OBJDIR = $(OBJDIR)vm/
VISU_OBJDIR = $(VM_OBJDIR)vs/
VM_OBJ = $(addprefix $(VM_OBJDIR), $(VM_SRC_LIST:.c=.o))
VISU_OBJ = $(addprefix $(VISU_OBJDIR), $(VISU_SRC_LIST:.c=.o))

LIB = libft.a
LIBDIR = ./libft/

INCLUDES = \
	-I $(LIBDIR)\
	-I ./includes/\
	-I ./vm/

FLAGS = -O3
GREEN = \033[92m
RESET = \033[0m

all: $(NAME)

$(NAME): $(LIB) $(OBJDIR) $(VM_OBJDIR) $(VISU_OBJDIR) $(VM_OBJ) $(VISU_OBJ)
	gcc $(FLAGS) -o $(NAME) $(VM_OBJ) $(VISU_OBJ) -L $(LIBDIR) -lft -lncurses
	@echo "$(GREEN)[Compilation Done]$(RESET)"

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@echo "$(GREEN)$(OBJDIR): was created$(RESET)"

$(VM_OBJDIR):
	@mkdir -p $(VM_OBJDIR)
	@echo "$(GREEN)$(VM_OBJDIR): was created$(RESET)"

$(VISU_OBJDIR):
	@mkdir -p $(VISU_OBJDIR)
	@echo "$(GREEN)$(VISU_OBJDIR): was created$(RESET)"

$(VM_OBJDIR)%.o: $(VM_SRCDIR)%.c
	@echo "Compiling Virtual Machine's Objects..."
	@gcc $(FLAGS) -c $< -o $@ $(INCLUDES)

$(VISU_OBJDIR)%.o: $(VISU_SRCDIR)%.c
	@echo "Compiling Visualizer's Objects..."
	@gcc $(FLAGS) -c $< -o $@ $(INCLUDES)

$(LIB):
	@echo "Compiling Libft..."
	@make -C $(LIBDIR) --silent
	@echo "$(GREEN)[Done]$(RESET)"

clean:
	@echo "Removing Object Files..."
	@make clean -C $(LIBDIR) --silent
	@rm -rf $(OBJDIR)
	@echo "$(GREEN)[Done]$(RESET)"

fclean: clean
	@echo "Removing Binary..."
	@make fclean -C $(LIBDIR) --silent
	@rm -f $(NAME)
	@echo "$(GREEN)[Done]$(RESET)"

re: fclean all

run: all
	clear
	./corewar katchup.cor katchup.cor katchup.cor katchup.cor
