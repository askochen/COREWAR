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

NAME = ../asm

CC = gcc

LIBFT = libft/libft.a

SRC = main.c read_file.c pars_line.c tools.c \
		param_tools.c pars_code.c label_tools.c \
		check_param.c code_tools.c op.c split_tools.c \
		asm_main.c asm_write.c convert_label.c encoding.c \
		params.c

OBJ = $(SRC:.c=.o)

HEADERS = libft/libft.h asm.h libft/get_next_line.h op.h

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) 
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT)

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
