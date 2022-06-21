# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gafreita <gafreita@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/15 14:15:30 by gafreita          #+#    #+#              #
#    Updated: 2022/06/21 21:21:51 by gafreita         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = pipex

SRCS =	parse.c \
		main.c \
		pipex.c \
		child_process.c \
		heredoc.c

OBJS = $(SRCS:%.c=%.o)

CC = gcc -Wall -Wextra -Werror

INCLUDES = -ILIBFT/libft/

LIB_DIR = LIBFT/libft/

COLOUR_GREEN=\033[7;1;32m
COLOUR_END=\033[0m
COLOUR_YELLOW=\033[0;33m

# ^ primeira dependencia
# @ nome da regra

$(NAME): $(OBJS) | libft
	@$(CC) $(^) -L$(LIB_DIR) -lft -o $(@)
	@echo "$(COLOUR_GREEN) >>> PIPEX OK <<< $(COLOUR_END)"

submodule:
	@git submodule update --init --recursive

all: $(NAME) submodule

valgrind: re
	@ valgrind --show-leak-kinds=all --leak-check=full ./pipex infile "grep a" "grep b" "wc -l" out

%.o: %.c
	@$(CC) $(INCLUDES) -c $(^) -o $(@)

libft:
	@make -C $(LIB_DIR)

clean:
	@make clean -C $(LIB_DIR)
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIB_DIR)
	@rm -f $(NAME)
	@rm -f out *.txt

re: fclean all

.PHONY: all clean fclean re libft submodule
