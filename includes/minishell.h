/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 11:05:02 by mde-figu          #+#    #+#             */
/*   Updated: 2021/10/07 01:49:15 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define INT_MAX 2147483647
# define HASH_SIZE 256

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

typedef struct s_ht_item
{
	char	*key;
	char	*value;
}	t_ht_item;

typedef struct s_hash_table
{
	t_ht_item					**items;
	int			size;
	int			count;
} t_hash_table;

typedef struct s_shell
{
	t_hash_table *hash;
	t_hash_table *env;
	int status_error;
}	t_shell;

t_shell	g_shell;

/*
** MAIN
*/

char	**blank_spaces(char *cmd);
void	ft_free_split(char **str);
void	execute(char **command);
char	*find_old_pwd(char **str);
void	print_split(char **str);
int		ft_strnstr_indie(const char *big, const char *small, size_t len);
void	env();

char	*search_hash_by_key(char *key);

/*
** HASH TABLE
*/

t_hash_table	*create_hash_table(int size);
t_ht_item		*create_hash_item(char* key, char* value);
t_ht_item		*insert_table(char *key, char *value);
t_hash_table	*envp_to_hash(char **envp);
void			free_item(t_ht_item *items);
void			free_table(t_hash_table *table);
void			free_all(t_hash_table *table);
void			free_item(t_ht_item *item);


#endif