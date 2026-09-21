# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Jpflegha <jpflegha@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/19 17:58:53 by Jpflegha          #+#    #+#              #
#    Updated: 2026/09/09 14:50:34 by Jpflegha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	RPN
CC =	c++
CFLAGS =	-Wall -Werror -Wextra -std=c++17 -O2
SRC =	main.cpp RPN.cpp
OBJ =	$(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all re clean fclean