# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csantos- <csantos-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/21 10:42:53 by mde-figu          #+#    #+#              #
#    Updated: 2021/10/08 23:30:46 by csantos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Wextra -Werror
INCLUDES = includes/minishell.h libraries/libft/libft.h
#LIBFT = libft
LIBFT = libraries/libft
#PRINTF = libraries/ft_printf


SRC = main.c hashtable.c hash_by_key.c changedir.c echo_env_pwd.c export.c\
		variable.c

all: $(NAME)

$(NAME): $(OBJ)
		make -C $(LIBFT)
		gcc $(CFLAGS) -g -o $(NAME) $(SRC) -L$(LIBFT) -lft -lreadline -lncurses -I includes -fsanitize=address

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