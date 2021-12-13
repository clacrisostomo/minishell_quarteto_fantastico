# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfico-vi <cfico-vi@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/21 10:42:53 by mde-figu          #+#    #+#              #
#    Updated: 2021/12/13 14:56:39 by cfico-vi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Wextra -Werror
INCLUDES = ../includes/minishell.h libraries/libft/libft.h
LIBFT = libraries/libft
SRC_PATH = ./source/


SRC = $(SRC_PATH)main.c\
			$(SRC_PATH)variable_env_local/arraytable.c\
			$(SRC_PATH)variable_env_local/array_by_key.c\
			$(SRC_PATH)variable_env_local/array_to_str_arr.c\
			$(SRC_PATH)variable_env_local/variable.c\
			$(SRC_PATH)variable_env_local/free_table.c\
			$(SRC_PATH)builtins/changedir.c\
			$(SRC_PATH)builtins/changedir_control.c\
			$(SRC_PATH)builtins/echo_env_pwd.c\
			$(SRC_PATH)builtins/export.c\
			$(SRC_PATH)builtins/export_only.c\
			$(SRC_PATH)builtins/export_utils.c\
			$(SRC_PATH)builtins/unset.c\
			$(SRC_PATH)parser/split_command_0.c\
			$(SRC_PATH)parser/split_command_1.c\
			$(SRC_PATH)parser/split_command_2.c\
			$(SRC_PATH)parser/split_control_0.c\
			$(SRC_PATH)parser/split_control_1.c\
			$(SRC_PATH)parser/split_control_2.c\
			$(SRC_PATH)parser/set_space_for_redir.c\
			$(SRC_PATH)pipe_redirect/cmd_for_redirect.c\
			$(SRC_PATH)pipe_redirect/logic_fd.c\
			$(SRC_PATH)pipe_redirect/miss_pipe.c\
			$(SRC_PATH)pipe_redirect/mister_redirect.c\
			$(SRC_PATH)pipe_redirect/here_doc.c\
			$(SRC_PATH)execute/execute.c\
			$(SRC_PATH)execute/execve.c\
			$(SRC_PATH)is_path.c\
			$(SRC_PATH)signal.c\
			$(SRC_PATH)paths_n_prompt.c

all: $(NAME)

$(NAME): $(OBJ)
		make -C $(LIBFT)
		gcc $(CFLAGS) -g -o $(NAME) $(SRC) -L $(LIBFT) -lft -lreadline -I includes

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
