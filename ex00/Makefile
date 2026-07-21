# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Jpflegha <jpflegha@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/19 17:58:53 by Jpflegha          #+#    #+#              #
#    Updated: 2026/07/19 17:59:42 by Jpflegha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	bte
CC =	c++
CFLAGS =	-Wall -Werror -Wextra -std=c++17
SRC =	main.cpp BitcoinExchange.cpp
OBJ =	$(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CC) $(CLFAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all re clean fclean