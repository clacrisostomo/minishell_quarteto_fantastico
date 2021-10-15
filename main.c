/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-figu <mde-figu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 20:52:52 by mde-figu          #+#    #+#             */
/*   Updated: 2021/10/15 00:25:22 by mde-figu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_strnstr_indie(const char *big, const char *small, size_t len)
{
	size_t	needle_len;
	char	*tmp;
	int i;
	i = 0;
	tmp = (char *)big;
	needle_len = ft_strlen(small);
	if (!needle_len)
		return (0);
	while (*tmp && len >= needle_len)
	{
		if (ft_strncmp(tmp, small, needle_len) == 0)
			return (i + needle_len);
		tmp++;
		i++;
	}
	return (INT_MAX); //só está assim pq se não tiver nada não fica como 0
}

void	print_split(char **str)
{
	int	i;

	i = -1;
	while (*(str + ++i) != NULL)
		ft_printf("%s\n", *(str + i));
}

void	execute(char **cmd)
{
	if (!(ft_strcmp(cmd[0], "echo")))
		echo(cmd);
	else if (!(ft_strcmp(cmd[0], "cd")))
		cd(cmd);
	else if (!(ft_strcmp(cmd[0], "pwd")))
		pwd();
	else if (!(ft_strcmp(cmd[0], "env")))
		env();
	else if (!(ft_strcmp(cmd[0], "export")))
		expt(cmd, 1);
	else if (!(ft_strcmp(cmd[0], "unset")))
		unset_(cmd);
	else if (ft_isvar(cmd))
		expt(cmd, 0);
	else
		ft_printf("%s: command not found\n", cmd[0]);
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
// 	ft_printf("echo %i, cd %i, pwd %i", posit->pos_echo, posit->pos_cd, posit->pos_pwd);
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

static void loop()
{
	char **cmd;
	char *command;
	char *prompt;
	//t_pos posit;

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
		quote_commander(cmd);
		execute(cmd);
		ft_free_split(cmd);

	}
	free_all(g_shell.env);
	//free_all(g_shell.hash);
	//free_all(g_shell.temp);
}

int main(int argc, char *argv[], char *envp[])
{
	//(void)argc;
	//(void)argv;
	//(void)envp;
	if (argc > 1 && argv)
	{
		ft_printf("ERROR: TOO MANY ARGS");
		return (0);
	}
//	print_split(envp);
	g_shell.env = envp_to_hash(envp);
	g_shell.hash = create_hash_table(50);
	g_shell.temp = create_hash_table(50);
	loop();
	return (1);
}
