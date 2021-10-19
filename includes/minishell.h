/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfico-vi <cfico-vi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 11:05:02 by mde-figu          #+#    #+#             */
/*   Updated: 2021/10/18 23:04:33 by cfico-vi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define INT_MAX 2147483647
# define HASH_SIZE 256 //ver se vai precisar depois
# define NONE 0
# define ENV 1
# define HASH 2
# define TEMP 3
# define TRUE 1
# define FALSE 0
# define S_QUOTE '\''
# define D_QUOTE '\"'
# define JOK_C '@'

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/file.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libraries/libft/libft.h"

// typedef struct s_pos
// {
// 	int	pos_echo;
// 	int pos_cd;
// 	int pos_pwd;
// 	int	pos_exp;
// 	int pos_uset;
// 	int pos_env;
// } t_pos;

typedef struct s_joker_m
{
	int					split_c;
	int					*id;
	int					id_size;
	struct s_joker_m	*next_jok;
}	t_joker_m;

typedef struct s_ht_item
{
	char	*key;
	char	*value;
}	t_ht_item;

typedef struct s_hash_table
{
	t_ht_item	**item;
	int			size;
	int			count;
}	t_hash_table;

typedef struct s_shell
{
	t_hash_table	*hash;
	t_hash_table	*env;
	t_hash_table	*temp;
	int				status_error;
}	t_shell;

t_shell	g_shell;

/*
** MAIN
*/

char			*blank_spaces(char *cmd);
void			ft_free_split(char **str);
void			execute(char **command);
char			*find_old_pwd(char **str);
void			print_split(char **str);
int				ft_strnstr_indie(const char *big, const char *small,
					size_t len);
int				ft_isvar(char **cmd);
char			**split_command(char *command);
void			quote_commander(char **cmd);
char			*search_hash_by_key(char *key);

/*
** COMMANDERS
*/

int				cd(char **cmd);
void			env(void);
void			pwd(void);
int				echo(char **cmd);
void			expt(char **cmd, int exp);
void			unset_(char **cmd);

/*
** HASH TABLE
*/

void			modify_hash_by_key(char *key, char *new_val);
char			*search_hash_by_key(char *key);
char			*find_key(char *line);
char			*find_value(char *line);
t_hash_table	*create_hash_table(int size);
t_ht_item		*create_hash_item(char *key, char*value);
t_ht_item		*insert_table(char *key, char *value);
t_hash_table	*envp_to_hash(char **envp);
void			free_item(t_ht_item *item);
void			free_table(t_hash_table *table);
void			free_all(t_hash_table *table);
void			free_item(t_ht_item *item);
//int				loop_table_n_insert(t_ht_item *item, int table);
int				loop_table_n_insert(char *key, char *value, int table);
int				modify_table_by_key(int table, char *key, char *value);




#endif
