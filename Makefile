# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/05 18:54:14 by mdjemaa           #+#    #+#              #
#    Updated: 2023/05/05 19:14:14 by mdjemaa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BOLD	:= \033[1m
BLACK	:= \033[30;1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
YELLOW	:= \033[33;1m
BLUE	:= \033[34;1m
MAGENTA	:= \033[35;1m
CYAN	:= \033[36;1m
WHITE	:= \033[37;1m
RESET	:= \033[0m

CC := gcc
CFLAGS := -Wall -Wextra -Werror
SANITIZE := -fsanitize=address
LIBFT := ./libft/libft.a
NAME := minishell
SRC :=	minishell.c\
		ms_cd.c\
		ms_crash.c\
		ms_echo.c\
		ms_env.c\
		ms_exit.c\
		ms_export.c\
		ms_parsing.c\
		ms_parsing_utils.c\
		ms_parsing_utils2.c\
		ms_pwd.c\
		ms_signals.c\
		ms_split.c\
		ms_terminal.c\
		ms_unset.c\

OBJ := $(SRC:.c=.o)

all: lib $(NAME)

lib:
	@$(MAKE) -C ./libft/

.c.o:
	@printf '$(GREEN)Compiling: $(RESET)$<\n'
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline $(SANITIZE)
	@printf '$(RED)- $(NAME) done -$(RESET)\n'

clean:
	@printf '$(YELLOW)Cleaning $(NAME) $(RESET)\n'
	@rm -f $(OBJ)
	@$(MAKE) clean -C ./libft/

fclean: clean
	@rm -f $(NAME)

re: fclean all