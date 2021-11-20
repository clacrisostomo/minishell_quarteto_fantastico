/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-figu <mde-figu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 11:05:02 by mde-figu          #+#    #+#             */
/*   Updated: 2021/11/18 23:17:45 by mde-figu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define INT_MAX 2147483647
# define HASH_SIZE 256 //ver se vai precisar depois

# define NONE 0
# define ENV 1
# define LOCAL 2

# define TRUE 1
# define FALSE 0

# define S_QUOTE '\''
# define D_QUOTE '\"'
# define PIPE '|'
# define INPUT '<'
# define OUTPUT '>'
# define JOK_C '@'
# define STDIN 0
# define STDOUT 1
# define STDERR 2

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/file.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <sys/wait.h>
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

typedef struct s_cd
{
	char			*tmp;
	char			*home;
	char			*slash;
	int				i;
}	t_cd;

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
	int			count; //o que que é count??
}	t_hash_table;

typedef struct s_shell
{
	t_hash_table	*env;
	t_hash_table	*local;
	int				status_error;
}	t_shell;

t_shell	g_shell;

/*
** MAIN
*/
void			ft_free_split(char **str);
void			free_n_env(char **n_env);
void			execute(char **command, int i);
void			quote_commander(char **cmd);
void			delete_item(t_hash_table *table, char *key);
void			parser(char **cmd, int i, int *old_fd);
void			ms_pipe(char **cmd, int i, int *old_fd);

/*
** SET SPACE FOR REDIR
*/
char			*put_space_before(char *cmd, int i);
char			*put_space_after(char *cmd, int i);
char			*set_space_for_redir(char *cmd, int *i);

/*
** BUILT-INS
*/
int				cd(char **cmd);
void			env(void);
void			pwd(void);
int				echo(char **cmd);
void			expt(char **cmd, int exp);
void			export_only(void);
void			unset_(char **cmd);
void			exit_terminal(char **cmd, char	**n_env);

void	cd_error_file(char **cmd);
void	control_cd_minus_two(char **cmd, char *slash, char *home);
void	control_cd_minus(char *tmp);
char	*put_quotes(t_ht_item *new_env);
char	**env_with_quotes(void);
void	print_export_env(char **array, int fd);
void	error_export(char **cmd, int i);


/*
** HASH TABLE
*/
char			*search_hash_by_key(char *key);
void			modify_hash_by_key(char *key, char *new_val);
char			*find_key(char *line);
char			*find_value(char *line);
t_hash_table	*create_hash_table(int size);
t_ht_item		*create_hash_item(char *key, char*value);
t_ht_item		*insert_table(char *key, char *value);
t_hash_table	*envp_to_hash(char **envp);
void			free_item(t_ht_item *item);
void			free_table(t_hash_table *table);
void			free_n_exit(void);
void			free_item(t_ht_item *item);
int				loop_table_n_insert(char *key, char *value, int table);
int				modify_table_by_key(int table, char *key, char *value);
int				which_table_by_key(char *key);
void			change_val_by_table(t_hash_table *table, char *key, char *value, int c);

/*
** SIGNAL
*/
void			define_signals(void);
void			prompt_handler(int signal);
void			interrupt_process(int signal);

/*
** SPLIT COMMAND
*/
char			**split_command(char *command);
char			*expand_var(char *command, int idx);
char			*treat_command(char *command, t_joker_m *joker_list);
void			put_jokers_c(char *command, t_joker_m *joker_list, int *i,
					int q_id);
char			*subs_quote(char *command, int idx, char q_id);
int				count_string(char *command, int *idx, int *i, int q_id);
char			*expand_quote_var(char *command, int *idx, int q_id);
char			*expand_error(char *command, int i);
void			free_joker_list(t_joker_m *lst);

/*
** UTILS
*/
int				is_path(char **cmd, char **n_env);
int				ft_isvar(char **cmd);
int				ft_strnstr_indie(const char *big, const char *small,
					size_t len);
char			**hash_to_str_arr(t_hash_table *n_env);

#endif
