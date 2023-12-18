# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/18 21:16:33 by rlandolt          #+#    #+#              #
#    Updated: 2023/12/18 21:20:14 by rlandolt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf.a

SRC_PATH = ./srcs

SRC = fdf.c \
	$(SRC_PATH)/gnl.c \
	$(SRC_PATH)/gnl_utils.c \

CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
		ar -rcs $@ $(OBJ)
		cc -g -o fdf fdf.a -fsanitize=address

all: $(NAME)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all, bonus, clean, fclean, re
