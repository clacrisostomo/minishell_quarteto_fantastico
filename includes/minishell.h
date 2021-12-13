/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:47:15 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/10 18:18:40 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define INT_MAX 2147483647

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

# define FILE_TMP "/tmp/mr_temporary_file"

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

typedef struct s_array_table
{
	t_ht_item		**item;
	int				size;
}	t_array_table;

typedef struct s_shell
{
	t_array_table	*env;
	t_array_table	*local;
	int				status_error;
}	t_shell;

t_shell	g_shell;

/*
** MAIN
*/
void			ft_free_split(char **str);
void			free_n_env(char **n_env);
void			execute(char **command, char **old_cmd, int has_pipe);
void			quote_commander(char **cmd);
void			delete_item(t_array_table *table, char *key);
void			parser(char **cmd, int i, int *old_fd, int has_pipe);

/*
** PIPE AND REDIRECT
*/
int				miss_pipe(char **cmd, int i, int *old_fd, int has_pipe);
char			**cmd_till_pipe(char **cmd, int begin, int end);

char			**make_command_redirect(char **cmd, int i, int *save_fd);
void			mister_redirect(char *redirect, char *file, int *save_fd);
int				is_redirect(char *cmd);
int				have_file_after_redirect(char **cmd);
void			dr_here(char *eof, int *save_fd);
void			interrupt(int signal);
void			define_signals_exec(void);

/*
** FD
*/
void			save_origin_fd(int *save_fd);
void			reset_fd(int *save_fd);

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
void			exit_terminal(char **cmd, char	**n_env, char **old_cmd);

void			cd_error_file(char **cmd);
void			control_cd_minus_two(char **cmd, char *slash, char *home);
void			control_cd_minus(char *tmp);
char			*put_quotes(t_ht_item *new_env);
char			**env_with_quotes(void);
void			print_export_env(char **array, int fd);
void			error_export(char **cmd, int i);
int				is_builtins(char **cmd);
void			builtins(char **cmd, char **old_cmd, char **n_env,
					int has_pipe);

/*
** ARRAY TABLE
*/
char			*search_array_by_key(char *key);
void			modify_array_by_key(char *key, char *new_val);
char			*find_key(char *line);
char			*find_value(char *line);
t_array_table	*create_array_table(int size);
t_ht_item		*create_array_item(char *key, char*value);
t_ht_item		*insert_table(char *key, char *value);
t_array_table	*envp_to_array(char **envp);
void			free_item(t_ht_item *item);
void			free_table(t_array_table *table);
void			free_n_exit(void);
void			free_item(t_ht_item *item);
int				loop_table_n_insert(char *key, char *value, int table);
int				modify_table_by_key(int table, char *key, char *value);
int				which_table_by_key(char *key);
void			insert_or_modify_by_key(char *key, char *new_val);
void			change_val_by_table(t_array_table *table, char *key,
					char *value, int c);

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
char			*swap_var(char *command, int i, int idx);

/*
** PATH HANDLERS
*/
char			*get_path_str(void);
char			**get_paths(void);
char			*do_prompt(void);
int				is_path(char **cmd, char **n_env);
char			**create_command_for_exec(char **cmd, char **paths);
void			do_exec(char **cmd, char **n_env);

/*
** UTILS
*/
int				ft_isvar(char **cmd);
int				ft_strnstr_indie(const char *big, const char *small,
					size_t len);
char			**array_to_str_arr(t_array_table *n_env);

#endif
