/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-figu <mde-figu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 20:52:52 by mde-figu          #+#    #+#             */
/*   Updated: 2021/10/04 22:39:48 by mde-figu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strnstr_indie(const char *big, const char *small, size_t len)
{
	size_t	needle_len;
	char	*tmp;
	int i;
	//printf("%s\n", big);
	//printf("%s\n", small);
	i = 0;
	tmp = (char *)big;
	needle_len = ft_strlen(small);
	//printf("%li\n", len);
	//printf("%li\n", needle_len);
	if (!needle_len)
		return (0);
	while (*tmp && len >= needle_len)
	{
		//printf("%i\n", ft_strncmp(tmp, small, needle_len));
		if (ft_strncmp(tmp, small, needle_len) == 0)
		{
		//printf("%li\n", i + needle_len);
			return (i + needle_len);
		}
		//needle_len++;
		tmp++;
		i++;
		//len--;
	}
	return (INT_MAX); //só está assim pq se não tiver nada não fica como 0
}

static void	pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (pwd != NULL)
		printf("%s\n", pwd);
	free(pwd);
}

void	print_split(char **str)
{
	int	i;

	i = -1;
	while (*(str + ++i) != NULL)
		printf("%s\n", *(str + i));
}

/*char	*find_old_pwd(char **str)
{
	int	i;

	i = -1;
	while (*(str + ++i) != NULL)
	{
		if(!ft_strncmp(*(str + i), "OLDPWD=", 7))
			return(ft_strchr(*(str + i), '=') + 1);
	}
	return("\0");
}*/


static int echo(char **cmd)
{
	int has_n;
	int i;
	//char 	*temp;
	//int		start;
	//printf("cheguei aqui!\n");
	has_n = 0;
	i = 1;
	if (ft_strcmp(cmd[1],"-n") == 0)
	{
		has_n = 1;
		i++;
	}
	while (cmd && cmd[i])
	{
		printf("%s ", cmd[i]);
		i++;
	}
/* 	if (ft_strncmp(cmd, "echo -n ", 8) == 0)
	{
		//has_n = 1;
		start = ft_strnstr_indie(cmd, "echo -n ", ft_strlen(cmd));
		temp = ft_substr(cmd, start, (ft_strlen(cmd) - start + 1));
		printf("%s", temp);
	}
	else
	{
		start = ft_strnstr_indie(cmd, "echo ", ft_strlen(cmd));
		temp = ft_substr(cmd, start, (ft_strlen(cmd) - start + 1));
		printf("%s\n", temp);
	} */
	if (has_n != 1)
		printf("\n");
	//free (temp);
	return (1);
}

void	env()
{
	int	c;

	c = 0;
	while(c <= g_shell.hash->size - 1)
	{
		printf("%s=%s\n", g_shell.hash->items[c]->key, g_shell.hash->items[c]->value);
		c++;
	}
}

char	*search_hash_by_key(char *key)
{
	int	c;

	c = 0;
	while(c <= g_shell.hash->size - 1)
	{
		//printf("%s = %s\n", g_shell.hash->items[c]->key, g_shell.hash->items[c]->value);
		if (ft_strncmp(g_shell.hash->items[c]->key, key, ft_strlen(key)) == 0)
		{
			//printf("%s\n", g_shell.hash->items[c]->value);
			return(g_shell.hash->items[c]->value);
		}
		c++;
	}
	return (NULL);
}

void	modify_hash_by_key(char *key, char *new_val)
{
	int	c;

	c = 0;
	while(c <= g_shell.hash->size - 1)
	{
		//printf("%s = %s\n", g_shell.hash->items[c]->key, g_shell.hash->items[c]->value);
		if (ft_strncmp(g_shell.hash->items[c]->key, key, ft_strlen(key)) == 0)
		{
			//printf("VAL: %s\n", new_val);
			//printf("OLD VALUE: %s\n", g_shell.hash->items[c]->value);
			free_item(g_shell.hash->items[c]);
				g_shell.hash->items[c] = insert_table(key, new_val);
			//printf("NEW VALUE: %s\n", g_shell.hash->items[c]->value);
		}
		c++;
	}
}

static int cd(char **cmd)
{
	char	*old;
	char	*tmp;
	char	*home;
	int		i;

	i = 1;
	tmp = NULL;
	home = search_hash_by_key("HOME");
	while (cmd[i])
		i++;
	if (i > 2)
	{
		printf("Minishell: cd's argument is wrong\n");
		g_shell.status_error = 1;
		return (1);
	}
	tmp = getcwd(tmp, 0);
	if (i == 1)
	{
		modify_hash_by_key("OLDPWD", tmp);
		chdir(home);
	}
	if (i == 2)
	{
		if (ft_strncmp(cmd[1], "-", 4) == 0)
		{
			old = search_hash_by_key("OLDPWD");
			printf("%s\n", old);
			chdir(old);
		}
		else if (ft_strncmp(cmd[1], "~-", 5) == 0)
		{
			old = search_hash_by_key("OLDPWD");
			chdir(old);
		}
		else if (ft_strncmp(cmd[1], "~", 4) == 0)
			chdir(home);
		else
			chdir(cmd[1]);
		modify_hash_by_key("OLDPWD", tmp);
	}
	free(tmp);
	return (0);
}

void	execute(char **command)
{
	if (!(ft_strcmp(command[0], "echo")))
		echo(command);
	else if (!(ft_strcmp(command[0], "cd")))
		cd(command);
	else if (!(ft_strcmp(command[0], "pwd")))
		pwd();
	else if (!(ft_strcmp(command[0], "env")))
		env();
}


/*static void init_pos(char *command, t_pos *posit)
{
	posit->pos_echo = ft_strnstr_indie(command, "echo", ft_strlen(command));
	posit->pos_cd = ft_strnstr_indie(command, "cd", ft_strlen(command));
	posit->pos_pwd = ft_strnstr_indie(command, "pwd", ft_strlen(command));
	posit->pos_exp = ft_strnstr_indie(command, "export", ft_strlen(command));
	posit->pos_uset = ft_strnstr_indie(command, "unset", ft_strlen(command));
	posit->pos_env = ft_strnstr_indie(command, "env", ft_strlen(command));
}*/

// static void parser(char *command, t_pos *posit)
// {
// 	init_pos(command, posit);
// 	printf("echo %i, cd %i, pwd %i", posit->pos_echo, posit->pos_cd, posit->pos_pwd);
// 	if (posit->pos_echo < posit->pos_cd)
// 		echo(command);
// 	else if (ft_strncmp(command, "cd ", 2) == 0)
// 		cd(command);
// 	//else if (!strcmp("exit", command))
// 	//exit();
// }

static char *do_prompt(void)
{
	char cwd[2048];
	char *prompt;

	getcwd(cwd, 2048);
	prompt = ft_strjoin(cwd, "$ ");
	return (prompt);
}
void	ft_free_split(char **str)
{
	int	i;

	i = -1;
	if (!(str))
		return ;
	while (*(str + ++i) != NULL)
	{
		free(*(str + i));
		*(str + i) = NULL;
	}
	free(str);
	str = NULL;
}
char	**blank_spaces(char *cmd)
{
	char **arg_cmd;

	arg_cmd = ft_split(cmd, ' ');
	return (arg_cmd);
}

static void loop(char **envp)
{
	char **cmd;
	char *command;
	char *prompt;
	//t_pos posit;

	envp_to_hash(envp);
	while (1)
	{
		g_shell.status_error = 0;
		prompt = do_prompt();
		command = readline(prompt);
		free(prompt);
		if (!strcmp("exit", command))
		{
			free(command);
			break;
		}
		add_history(command);
		cmd = blank_spaces(command);
		free(command);
		//parser(command, &posit);
		execute(cmd);
		ft_free_split(cmd);
		//cd(command);
		//exec_cmd_two(command);
	}
	//while (g_shell.hash->items - 1)
	//{
	//	free_item(g_shell.hash->items++);
	//}
	//free_table(g_shell.hash);
	free_all(g_shell.hash);
	//free(g_shell.hash);
}

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	(void)envp;
	if (argc > 1 && argv)
	{
		printf("ERROR: TOO MANY ARGS");
		return (0);
	}
//	print_split(envp);
	loop(envp);
	return (1);
}
