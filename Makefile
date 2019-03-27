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

VM = corewar
ASM = asm

VM_SRCDIR = vm/
VM_SRC_LIST = \
	main.c\
	additional_lib.c\
	arg_validation.c\
	champ_data.c\
	codage.c\
	do_turn.c\
	vm_auxiliary.c\
	initialization.c\
	intro_champs.c\
	operations.c\
	operations2.c\
	op_auxiliary.c\
	print_board.c

VISU_SRCDIR = $(VM_SRCDIR)visu/
VISU_SRC_LIST = \
	visu.c\
	window_funcs.c\
	draw_board.c\
	draw_info.c\
	init.c

ASM_SRCDIR = asm/
ASM_SRC_LIST =\
	main.c\
	additional.c\
	binary_writing.c\
	command_and_lable_validation.c\
	reading_from_file.c\
	tokenizing.c

OBJDIR = ./obj/
VM_OBJDIR = $(OBJDIR)vm/
VISU_OBJDIR = $(VM_OBJDIR)vs/
ASM_OBJDIR = $(OBJDIR)asm/
VM_OBJ = $(addprefix $(VM_OBJDIR), $(VM_SRC_LIST:.c=.o))
VISU_OBJ = $(addprefix $(VISU_OBJDIR), $(VISU_SRC_LIST:.c=.o))
ASM_OBJ = $(addprefix $(ASM_OBJDIR), $(ASM_SRC_LIST:.c=.o))

LIB = libft.a
LIBDIR = ./libft/

INCLUDES = \
	-I $(LIBDIR)\
	-I ./includes/\
	-I ./vm/

FLAGS = -O2 ##FLAGS
GREEN = \033[92m
RESET = \033[0m

all: $(VM) $(ASM)

$(ASM): $(LIB) $(OBJDIR) $(ASM_OBJDIR) $(ASM_OBJ)
	@echo "Compiling Assembler..."
	gcc $(FLAGS) -o $(ASM) $(ASM_OBJ) ./includes/op.c -L $(LIBDIR) -lft
	@echo "$(GREEN)[Compilation Done]$(RESET)"

$(VM): $(LIB) $(OBJDIR) $(VM_OBJDIR) $(VISU_OBJDIR) $(VM_OBJ) $(VISU_OBJ)
	@echo "Compiling Virtual Machine..."
	gcc $(FLAGS) -o $(VM) $(VM_OBJ) $(VISU_OBJ) ./includes/op.c -L $(LIBDIR) -lft -lncurses
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

$(ASM_OBJDIR):
	@mkdir -p $(ASM_OBJDIR)
	@echo "$(GREEN)$(ASM_OBJDIR): was created$(RESET)"

$(VM_OBJDIR)%.o: $(VM_SRCDIR)%.c
	@echo "Compiling Virtual Machine's Objects..."
	@gcc $(FLAGS) -c $< -o $@ $(INCLUDES)

$(VISU_OBJDIR)%.o: $(VISU_SRCDIR)%.c
	@echo "Compiling Visualizer's Objects..."
	@gcc $(FLAGS) -c $< -o $@ $(INCLUDES)

$(ASM_OBJDIR)%.o: $(ASM_SRCDIR)%.c
	@echo "Compiling Assembler's Objects..."
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
	@rm -f $(VM)
	@rm -f $(ASM)
	@echo "$(GREEN)[Done]$(RESET)"

re: fclean all

run: all
	clear
	./corewar -visual ../test_process_1.cor
