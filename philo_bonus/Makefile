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

SRC = Philosophers.c init.c routine.c print.c 

CC = @gcc -pthread $(SRC) 

CFLAGS = -Wall -Wextra -Werror

DEBUG = -fsanitize=address -g

OBJC = $(SRC:.c=.o)

RM = @rm -f

$(NAME) : $(SRC)
			$(CC) -o $(NAME)

all : $(NAME)

debug :
	gcc $(CFLAGS) $(DEBUG) $(SRC) -o $(NAME)

clean :

fclean :
			$(RM) $(NAME)

re : fclean all

.PHONY:			all clean fclean re