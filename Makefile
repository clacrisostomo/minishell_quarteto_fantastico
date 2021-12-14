# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/21 10:42:53 by mde-figu          #+#    #+#              #
#    Updated: 2021/12/14 01:18:19 by mmoreira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Wextra -Werror
INCLUDES = ./includes/minishell.h libraries/libft/libft.h
LIBFT = libraries/libft

SRC_PATH =	./source \
			./source/variable_env_local/ \
			./source/builtins/ \
			./source/parser/ \
			./source/pipe_redirect/ \
			./source/execute/

SRC =		main.c\
			arraytable.c\
			array_by_key.c\
			array_to_str_arr.c\
			variable.c\
			free_table.c\
			changedir.c\
			changedir_control.c\
			echo_env_pwd.c\
			export.c\
			export_only.c\
			export_utils.c\
			unset.c\
			split_command_0.c\
			split_command_1.c\
			split_command_2.c\
			split_control_0.c\
			split_control_1.c\
			split_control_2.c\
			set_space_for_redir.c\
			cmd_for_redirect.c\
			logic_fd.c\
			miss_pipe.c\
			mister_redirect.c\
			here_doc.c\
			execute.c\
			execve.c\
			is_path.c\
			signal.c\
			paths_n_prompt.c

OBJ_DIR	=	./builds
OBJ		=	$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

vpath %.c $(SRC_PATH)

all: $(NAME)

$(NAME): $(OBJ)
		make -C $(LIBFT)
		gcc $(CFLAGS) -g -o $(NAME) $(OBJ) -L $(LIBFT) -lft -lreadline -I includes

$(OBJ_DIR)/%.o:	%.c ./includes/minishell.h
	mkdir -p $(OBJ_DIR)
	gcc -c -o $@ $(CFLAGS) -I includes $<

git:
	@git add .
	@git commit -m "$m"
	@git push
#make git m="blablabla"

clean:
		make clean -C $(LIBFT)
		rm -f $(OBJ)
		rm -rf ./buldis

fclean: clean
		make fclean -C $(LIBFT)
		rm -f $(NAME) $(OBJ)

re: fclean all
