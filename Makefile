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
CFLAGS := -Wall -Wextra -Werror -g -fsanitize=address
LIBFT := ./libft/libft.a
NAME := pipex
SRC :=	pipex.c\
		px_utils.c\

BSRC :=	pipex_bonus.c\
		px_utils.c\
		px_util_bonus.c\
		px_init_bonus.c\

OBJ := $(SRC:.c=.o)

BOBJ := $(BSRC:.c=.o)

all: lib $(NAME)

lib:
	@$(MAKE) -C ./libft/

.c.o:
	@printf '$(GREEN)Compiling: $(RESET)$<\n'
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

bonus: lib $(BOBJ)
	@$(CC) $(CFLAGS) $(BOBJ) $(LIBFT) -o $(NAME)
	@printf '$(RED)- Bonus done -$(RESET)\n'

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@printf '$(RED)- $(NAME) done -$(RESET)\n'

clean:
	@printf '$(YELLOW)Cleaning $(NAME) $(RESET)\n'
	@rm -f $(OBJ)
	@rm -f $(BOBJ)
	@$(MAKE) clean -C ./libft/

fclean: clean
	@rm -f $(NAME)

re: fclean all
