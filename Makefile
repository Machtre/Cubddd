# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbuisson <mbuisson@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/20 17:13:50 by mbuisson          #+#    #+#              #
#    Updated: 2026/01/21 20:19:32 by mbuisson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= parser

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g -I./includes

SRCDIR	= src
PARDIR	= $(SRCDIR)/parsing
GNLDIR = $(SRCDIR)/GNL

SRC		= $(PARDIR)/main.c \
		  $(PARDIR)/ft_split.c\
		  $(PARDIR)/ft_strtrim.c\
		  $(PARDIR)/parse_color.c \
		  $(PARDIR)/parse_map.c \
		  $(PARDIR)/parse_textures.c \
		  $(PARDIR)/parse.c \
		  $(PARDIR)/check_map.c \
		  $(PARDIR)/utils_parse.c\
		  $(PARDIR)/utils_parse2.c\
		  $(PARDIR)/utils_parse3.c\
		  $(GNLDIR)/get_next_line.c\
		  $(GNLDIR)/get_next_line_utils.c

OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

