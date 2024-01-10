# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/18 21:16:33 by rlandolt          #+#    #+#              #
#    Updated: 2024/01/10 12:35:04 by rlandolt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf.a

SRC_PATH = ./srcs
MLX = .minilibx/libmlx.a
MLX_FLAGS = -L.minilibx -Lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz

SRC = fdf.c \
	$(SRC_PATH)/gnl.c \
	$(SRC_PATH)/gnl_utils.c \
	$(SRC_PATH)/strings.c \
	$(SRC_PATH)/split.c \
	$(SRC_PATH)/input.c \
	$(SRC_PATH)/draw.c \
	$(SRC_PATH)/struct.c \
	$(SRC_PATH)/color.c \
	$(SRC_PATH)/transform.c \
	$(SRC_PATH)/hooks.c \

CC = cc -g
CFLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
		@ar -rcs $@ $(OBJ)
		@make -C .minilibx
		@${CC} -o fdf ${NAME} $(MLX) $(MLX_FLAGS)

all: $(NAME)

clean:
		rm -f $(OBJ)

fclean: clean
		@make clean -C .minilibx
		rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
