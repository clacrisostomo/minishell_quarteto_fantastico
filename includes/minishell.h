/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantos- <csantos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 11:05:02 by mde-figu          #+#    #+#             */
/*   Updated: 2021/09/28 22:11:28 by csantos-         ###   ########.fr       */
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

t_env	g_env;
typedef struct s_env
{
	int status_error;
}	t_env;
typedef struct s_pos
{
	int	pos_echo;
	int pos_cd;
	int pos_pwd;
	int	pos_exp;
	int pos_uset;
	int pos_env;
} t_pos;

typedef struct s_ht_item
{
	char	*key;
	char	*value;
}	t_ht_item;

typedef struct s_hash_table
{
	t_ht_item**	items;
	int			size;
	int			count;
} t_hash_table;



#endif