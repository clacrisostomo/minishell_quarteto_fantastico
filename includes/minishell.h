/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 11:05:02 by mde-figu          #+#    #+#             */
/*   Updated: 2021/09/23 02:52:29 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define INT_MAX 2147483647

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/file.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>
#include "../libraries/libft/libft.h"
//#include "../libraries/ft_printf/ft_printf.h"

typedef struct s_pos
{
	int	pos_echo;
	int pos_cd;
	int pos_pwd;
	int	pos_exp;
	int pos_uset;
	int pos_env;
} t_pos;


#endif