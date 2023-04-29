# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/19 15:12:46 by rficht            #+#    #+#              #
#    Updated: 2023/04/29 14:44:19 by mdjemaa          ###   ########.fr        #
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

#avoid inheriting variables from the environement
SHELL = /bin/sh

#Sometimes you may need to set suffixes manualy
#.SUFFIXES:
#.SUFFIXES: .c .o

#set the program name as current directory
DIR_PATH = $(shell pwd)
NAME = mini_shell
AR_NAME = $(NAME).a

#general compilation flags
CFLAG = -Wall -Wextra -Werror -fsanitize=address

# Definition of sources (.c from libft + curr dir def by hand)
SOURCES =	main.c
			
OBJ = $(SOURCES:.c=.o)

# Compiler used for this project
CC = cc

# main rule called by default
all: $(NAME)

# rule for compile .c -> .o
%.o : %.c
	@$(CC) $(CFLAG) -o $@ -c $<

# rule to make an archive of the project
$(AR_NAME): $(OBJ)
	@ar rc $@ $^

# create a program assuming that main is contained inside a main.c
$(NAME): $(AR_NAME)
	@$(CC) $(CFLAG) $(GFLAG) -o $(NAME) -g $(AR_NAME) -g3 -lreadline

# create prog and launch it
test: all
	./$(NAME)
	
# remove .o corresponding to sources	
clean: 
	@rm -f $(OBJ)

# remove .o and .a corresponding to sources
fclean: clean
	@rm -f $(AR_NAME) $(NAME)

# force to recompile everything
re: fclean $(AR_NAME)

#help:
#	@echo 'Sources:'
#	@echo $(SOURCES)

#target: dependencies
#		recipies
# $@ target name
# $< first dependencie
# $^ dependencies list
# $? dependencies that ar more recent than target
