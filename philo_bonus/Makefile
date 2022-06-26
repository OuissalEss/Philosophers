# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/05 06:58:42 by oessamdi          #+#    #+#              #
#    Updated: 2022/06/17 10:51:24 by oessamdi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRC = philosophers_bonus.c init_bonus.c routine_bonus.c print_bonus.c 

CC = @gcc

CFLAGS = -Wall -Wextra -Werror

DEBUG = -fsanitize=address -g

OBJC = $(SRC:.c=.o)

RM = @rm -f

$(NAME) : $(OBJC)
			$(CC) $(CFLAGS) -pthread $(OBJC) -o $(NAME)
			@echo "\033[1;32mPHILO CREATED!"

all : $(NAME)

debug :
	gcc  $(DEBUG) $(SRC) -o $(NAME)

clean :
		$(RM) *.o
		@echo "Removed all the .o files"
fclean :
		$(RM) *.o
		$(RM) $(NAME)
		@echo "Removed executble"

re : fclean all

.PHONY:			all clean fclean re