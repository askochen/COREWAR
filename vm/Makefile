#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: askochen <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/26 16:38:20 by askochen          #+#    #+#              #
#    Updated: 2017/07/05 20:07:10 by askochen         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ../corewar

CC = gcc

LIBFT = libft/libft.a

SRC = operators/live.c operators/ld.c \
operators/st.c operators/add.c operators/sub.c \
operators/and.c operators/or.c operators/xor.c \
operators/zjmp.c operators/ldi.c operators/sti.c \
operators/fork.c operators/lld.c operators/lldi.c \
operators/lfork.c operators/aff.c \
process_tools.c op.c exec_of_comands.c vm_main.c core_war.c \
decoding.c initialization.c list.c type_param.c valid_opcode.c \
validation_argc.c validation_argc_2.c validation_cor.c \
var_param.c write_rez.c validate_operation.c vis.c vis_key.c vis_static.c \
vis_print_changes.c delete_lst.c dump.c validate_opcode.c  \
validation_flag.c vis_part_changes.c

OBJ = $(SRC:.c=.o)

HEADERS = libft/libft.h corewar_vm.h libft/get_next_line.h op.h

FLAGS = -Wall 

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) 
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lncurses

$(OBJ): %.o: %.c
	$(CC) -c $(FLAGS) $< -o $@

$(LIBFT):
	make -C libft/

libft_clean:
	make -C libft/ clean

libft_fclean:
	make -C libft/ fclean

clean: libft_clean 
	rm -f $(OBJ) corewar.h.gch *~

fclean: clean libft_fclean 
	rm -f $(NAME)

re: fclean all
