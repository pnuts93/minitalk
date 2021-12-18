# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pnuti <pnuti@student.42wolfsburg.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/27 11:20:39 by pnuti             #+#    #+#              #
#    Updated: 2021/12/18 09:45:57 by pnuti            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS=		-Werror -Wall -Wextra
NAME=		client
S_NAME=		server
F_COMMON=	throw_error.c
F_CLIENT=	c_main.c
F_SERVER=	s_main.c
F_BONUS=	s_main.c

all : $(NAME)

$(NAME) : $(S_NAME)
	$(CC) $(FLAGS) $(F_CLIENT) $(F_COMMON) -o $@ -L libft/ -lft
$(S_NAME) : complib
	$(CC) $(FLAGS) $(F_SERVER) $(F_COMMON) -o $@ -L libft/ -lft
complib : download_lib
	cd libft/ && make
download_lib:
	ls libft/ || git clone https://github.com/pnuts93/libft.git
clean :
	cd libft/ && make clean
fclean :
	rm -f $(S_NAME) $(NAME)
	rm -fr libft
bonus : re
	rm -f $(S_NAME)
	$(CC) $(FLAGS) $(F_BONUS) $(F_COMMON) -o $(S_NAME) -L libft/ -lft
re : fclean all