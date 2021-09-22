# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mde-figu <mde-figu@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/20 12:07:51 by gkenzo-s          #+#    #+#              #
#    Updated: 2021/09/10 13:18:54 by mde-figu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
	  ft_memchr.c ft_memcmp.c ft_strlen.c ft_isalpha.c ft_isdigit.c \
	  ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
	  ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strlcpy.c ft_strlcat.c \
	  ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
	  ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
	  ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	  ft_putnbr_fd.c\

BONUS_SRC = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
			ft_lstmap.c

OBJ = ft_memset.o ft_bzero.o ft_memcpy.o ft_memccpy.o ft_memmove.o \
	  ft_memchr.o ft_memcmp.o ft_strlen.o ft_isalpha.o ft_isdigit.o \
	  ft_isalnum.o ft_isascii.o ft_isprint.o ft_toupper.o ft_tolower.o \
	  ft_strchr.o ft_strrchr.o ft_strncmp.o ft_strlcpy.o ft_strlcat.o \
	  ft_strnstr.o ft_atoi.o ft_calloc.o ft_strdup.o \
	  ft_substr.o ft_strjoin.o ft_strtrim.o ft_split.o ft_itoa.o \
	  ft_strmapi.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o \
	  ft_putnbr_fd.o 

BONUS_OBJ = ft_lstnew.o ft_lstadd_front.o ft_lstsize.o ft_lstlast.o \
			ft_lstadd_back.o ft_lstdelone.o ft_lstclear.o ft_lstiter.o \
			ft_lstmap.o

ADDITIONAL_SRC = ft_itohex.c ft_max_width.c ft_putchar.c ft_putstr.c \
				 ft_put_n_char.c ft_power_of.c ft_ftoa.c ft_strcmp.c \
				ft_strsplit.c

ADDITIONAL_OBJ = ft_itohex.o ft_max_width.o ft_putchar.o ft_putstr.o \
				 ft_put_n_char.o ft_power_of.o ft_ftoa.o ft_strcmp.o \
				ft_strsplit.o

all: $(NAME)

$(NAME): $(SRC) $(ADDITIONAL_SRC)
	@gcc -Wall -Wextra -Werror -c $(SRC) $(ADDITIONAL_SRC)
	@ar rc $(NAME) $(OBJ) $(ADDITIONAL_OBJ)
	@ranlib $(NAME)

bonus: $(SRC) $(BONUS_SRC) $(ADDITIONAL_SRC)
	@gcc -Wall -Wextra -Werror -c $(SRC) $(BONUS_SRC) $(ADDITIONAL_SRC)
	@ar rc $(NAME) $(OBJ) $(BONUS_OBJ) $(ADDITIONAL_OBJ)
	@ranlib $(NAME)

clean:
	@/bin/rm -f $(OBJ) $(BONUS_OBJ) $(ADDITIONAL_OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean fclean
