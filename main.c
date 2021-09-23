/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 20:52:52 by mde-figu          #+#    #+#             */
/*   Updated: 2021/09/23 11:15:55 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int echo(char *cmd)
{
	int have_n;

	have_n = 0;
	if (ft_strncmp(cmd, "echo -n", 7) == 0)
		have_n = 1;
	printf("%s", cmd);
	if (have_n != 1)
		printf("\n");
	return (1);
}

static int exec_cmd_one(char *cmd)
{
	char *tmp;
	char *space;

	space = ft_strchr(cmd, ' ') + 1;
	tmp = ft_substr(cmd, space - cmd, ft_strlen(space));
	chdir(tmp);
	free(tmp);

	/*if (ft_strncmp(cmd, "cd ", 2) == 0)
	{
		space = ft_strchr(cmd, ' ') + 1;
		tmp = ft_substr(cmd, space - cmd, ft_strlen(space));
		chdir(tmp);
		free (tmp);
	}*/
	return (1);
}

void execute(char *command)
{
	if (ft_strncmp(command, "echo ", 4) == 0)
		echo(command);
	else if (ft_strncmp(command, "cd ", 2) == 0)
		exec_cmd_one(command);
	//else if (!strcmp("exit", command))
	//exit();
}

int	ft_strnstr_indie(const char *big, const char *small, size_t len)
{
	size_t	needle_len;
	char	*tmp;
	int i;
	//printf("%s\n", big);
	printf("%s\n", small);
	i = 0;
	tmp = (char *)big;
	needle_len = ft_strlen(small);
	printf("%li\n", len);
	printf("%li\n", needle_len);
	if (!needle_len)
		return (0);
	while (*tmp && len >= needle_len)
	{
		//printf("%i\n", ft_strncmp(tmp, small, needle_len));
		if (ft_strncmp(tmp, small, needle_len) == 0)
		{
			printf("%li\n", i + needle_len);
			return (i + needle_len);
		}
		//needle_len++;
		tmp++;
		i++;
		//len--;
	}
	return (INT_MAX); //só está assim pq se não tiver nada não fica como 0
}

static void init_pos(char *command, t_pos *posit)
{
	posit->pos_echo = ft_strnstr_indie(command, "echo", ft_strlen(command));
	posit->pos_cd = ft_strnstr_indie(command, "cd", ft_strlen(command));
	posit->pos_pwd = ft_strnstr_indie(command, "pwd", ft_strlen(command));
	posit->pos_exp = ft_strnstr_indie(command, "export", ft_strlen(command));
	posit->pos_uset = ft_strnstr_indie(command, "unset", ft_strlen(command));
	posit->pos_env = ft_strnstr_indie(command, "env", ft_strlen(command));
}

static void parser(char *command, t_pos *posit)
{
	init_pos(command, posit);
	printf("echo %i, cd %i, pwd %i", posit->pos_echo, posit->pos_cd, posit->pos_pwd);
	if (posit->pos_echo < posit->pos_cd)
		echo(command);
	else if (ft_strncmp(command, "cd ", 2) == 0)
		exec_cmd_one(command);
	//else if (!strcmp("exit", command))
	//exit();
}

static char *do_prompt(void)
{
	char cwd[2048];
	char *prompt;

	getcwd(cwd, 2048);
	prompt = ft_strjoin(cwd, "$ ");
	return (prompt);
}

static void loop(void)
{
	char *command;
	char *prompt;
	t_pos posit;

	while (1)
	{
		prompt = do_prompt();
		command = readline(prompt);
		free(prompt);
		if (!strcmp("exit", command))
		{
			free(command);
			break;
		}
		parser(command, &posit);
		//exec_cmd_one(command);
		//exec_cmd_two(command);
		add_history(command);
		free(command);
	}
}

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	if (argc > 1 && argv)
	{
		printf("ERROR: TOO MANY ARGS");
		return (0);
	}
	loop();
	return (1);
}
