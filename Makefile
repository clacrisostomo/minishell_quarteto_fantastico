# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/21 10:42:53 by mde-figu          #+#    #+#              #
#    Updated: 2021/11/08 20:12:01 by nbarreir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Wextra -Werror
INCLUDES = includes/minishell.h libraries/libft/libft.h
LIBFT = libraries/libft


SRC = main.c hashtable.c hash_by_key.c changedir.c echo_env_pwd.c export.c\
		variable.c unset.c split_command_0.c is_path.c hash_to_str_arr.c signal.c\
		set_space_for_redir.c split_command_1.c split_command_2.c export_only.c\
		changedir_control.c export_utils.c

all: $(NAME)

$(NAME): $(OBJ)
		make -C $(LIBFT)
		gcc $(CFLAGS) -g -o $(NAME) $(SRC) -L $(LIBFT) -lft -lreadline -I includes -fsanitize=address

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
