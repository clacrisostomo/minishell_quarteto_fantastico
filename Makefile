# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/21 10:42:53 by mde-figu          #+#    #+#              #
#    Updated: 2021/09/23 00:58:41 by nbarreir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Wextra -Werror
INCLUDES = includes/minishell.h libraries/libft/libft.h
#LIBFT = libft
LIBFT = libraries/libft
#PRINTF = libraries/ft_printf


SRC = main.c\

all: $(NAME)

$(NAME): $(OBJ)
		make -C $(LIBFT)
		gcc $(CFLAGS) -fsanitize=address -g -o $(NAME) $(SRC) -L$(LIBFT) -lft -lreadline -lncurses -I includes

%.o: %.c
		gcc -c $< -I includes

git:
	@git add .
	@git commit -m "$m"
	@git push
#make git m="blablabla"

clean:
		make clean -C $(LIBFT)
		rm -f $(OBJ)

fclean: clean
		make fclean -C $(LIBFT)
		rm -f $(NAME) $(OBJ)

re: fclean all