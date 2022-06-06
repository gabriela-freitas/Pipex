# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gafreita <gafreita@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/02 21:42:28 by gafreita          #+#    #+#              #
#    Updated: 2022/06/06 19:46:52 by gafreita         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS =	pipex.c \
		parse.c \
		exec.c

OBJS = $(SRCS:%.c=%.o)

CC = gcc -Wall -Wextra -Werror

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

valgrind: re
	@ valgrind --show-leak-kinds=all --leak-check=full ./pipex in "ls -l" "grep w" out

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
