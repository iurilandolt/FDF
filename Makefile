# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/18 21:16:33 by rlandolt          #+#    #+#              #
#    Updated: 2023/12/19 18:26:41 by rlandolt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf.a

SRC_PATH = ./srcs

SRC = fdf.c \
	$(SRC_PATH)/gnl.c \
	$(SRC_PATH)/gnl_utils.c \
	$(SRC_PATH)/strings.c \
	$(SRC_PATH)/3D_array.c \
	$(SRC_PATH)/2D_array.c \

CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
		ar -rcs $@ $(OBJ)
		cc -g -o fdf fdf.a

all: $(NAME)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all, bonus, clean, fclean, re
