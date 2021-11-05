# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: natali <natali@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/14 12:16:39 by natali            #+#    #+#              #
#    Updated: 2021/11/05 07:28:47 by natali           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= scan_util

SRC		= ScannerClass.cpp \
		main.cpp

OBJ		= $(SRC:%.cpp=%.o)

CFLAGS	= -Wall -Werror -Wextra -std=c++11 -O3

all: 	$(NAME)

$(NAME):$(OBJ)
		clang++ $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
		clang++ $(CFLAGS) -c $< -o $@

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: 	fclean all

.PHONY: all clean fclean re run
