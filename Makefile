# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mde-figu <mde-figu@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/21 10:42:53 by mde-figu          #+#    #+#              #
#    Updated: 2021/09/21 22:06:28 by mde-figu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c\

INCLUDES = minishell.h libft.h
NAME = minishell
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft


all: $(NAME)

$(NAME): $(OBJ)
		make -C $(LIBFT)
		gcc $(CFLAGS) -fsanitize=address -g -o $(NAME) $(SRC) -L$(LIBFT) -lft -lreadline -lncurses -I includes

%.o: %.c
		gcc -c $< -I includes
		
clean:
		make clean -C $(LIBFT)
		rm -f $(OBJ)
		rm -f $(NAME)
fclean: clean
		make fclean -C $(LIBFT)
		rm -f $(OBJ)
re: fclean all