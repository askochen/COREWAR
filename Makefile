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

all: 
	make -C asembler/
	make -C vm/

clean:
	make -C asembler/ clean
	make -C vm/ clean

fclean:
	make -C asembler/ fclean
	make -C vm/ fclean

re: fclean all
