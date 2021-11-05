# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: natali <natali@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/14 12:16:39 by natali            #+#    #+#              #
#    Updated: 2021/11/05 21:03:47 by natali           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= scan_util

SRC		= ScannerClass.cpp \
		main.cpp

SRCS_DIR = srcs/

SRCS 	= $(addprefix $(SRCS_DIR), $(SRC))

OBJ		= $(SRCS:%.cpp=%.o)

DEPENDS = $(SRCS:%.cpp=%.d)

INC		= includes/

CFLAGS	= -Wall -Werror -Wextra -std=c++17 -O3

all: 	$(NAME)

$(NAME):$(OBJ)
		clang++ $(CFLAGS) -I $(INC) -o $(NAME) $(SRCS)

%.o: %.cpp
		clang++ $(CFLAGS) -I $(INC) -MMD -MP -c $< -o $@

clean:
		rm -f $(OBJ) $(DEPENDS)

fclean: clean
		rm -f $(NAME)

re: 	fclean all

.PHONY: all clean fclean re run
