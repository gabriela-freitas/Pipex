# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gafreita <gafreita@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/02 21:42:28 by gafreita          #+#    #+#              #
#    Updated: 2022/06/03 21:29:57 by gafreita         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = pipex.c

OBJS = $(SRCS:%.c=%.o)

CC = gcc -Wall -Wextra -Werror -fsanitize=address

INCLUDES = -ILIBFT/libft/

LIB_DIR = LIBFT/libft/

COLOUR_GREEN=\033[7;1;32m
COLOUR_END=\033[0m

# ^ primeira dependencia
# @ nome da regra

$(NAME): $(OBJS) | libft
	@$(CC) $(^) -L$(LIB_DIR) -lft -o $(@)
	@echo "$(COLOUR_GREEN) >>> PIPEX OK <<< $(COLOUR_END)"

submodule:
	@git submodule update --init --recursive

all: $(NAME)

%.o: %.c
	@$(CC) -g $(INCLUDES) -c $(^) -o $(@)

libft:
	@make -C $(LIB_DIR)

clean:
	@make clean -C $(LIB_DIR)
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIB_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft submodule
