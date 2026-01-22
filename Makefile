# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nguinot- <nguinot-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/13 14:41:11 by nguinot-          #+#    #+#              #
#    Updated: 2026/01/21 11:20:17 by nguinot-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
NAME = cub3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Iminilibx
MLX_DIR = ./minilibx
SRC = $(wildcard src/*.c src/movement/*.c src/rendering/*.c src/utils/*.c src/mlx/*.c src/main/*.c src/textures/*.c)
OBJ = $(SRC:.c=.o)

MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(MLX_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
