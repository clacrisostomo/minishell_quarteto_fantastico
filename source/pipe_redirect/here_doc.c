/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantos- <csantos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 22:53:24 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/01 00:29:59 by csantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	create_mr_temporary_file(void)
{
	int	file_fd;

	file_fd = open(FILE_TMP, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (file_fd == -1)
		printf("ERROR REDIRECT\n");
	return (file_fd);
}

void	interrupt_here_document(int signal)
{
	(void)signal;
	errno = 130;
	write(1, "\n", 1);
	exit(130);
}

void	dr_here(char *eof, int *save_fd)
{
	int file_tmp;
	int file_def;
	char *tmp;
	int	status;
	int save_out;
	int pid;

	save_out = dup(STDOUT);
	//dup2(save_fd[1], STDOUT);
	dup2(save_fd[0], STDIN);
	file_tmp = create_mr_temporary_file();
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, interrupt_here_document);
		while (1)
		{
			tmp = readline("> ");
			if (!tmp)
			{
				printf("ERROOOOOOOOR\n");
				close(file_tmp);
				exit(0);
			}
			if(tmp)
			{
				if (ft_strcmp(tmp, eof))
					ft_putendl_fd(tmp, file_tmp);
				if(!ft_strcmp(tmp, eof))
				{
					free(tmp);
					//dup2(file_tmp, save_fd[0]);
					close(file_tmp);
					break;
				}
			}
			free(tmp);
		}
		exit(errno);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
			errno = WIFEXITED(status);
	//unlink(FILE_TMP);
	file_def = open(FILE_TMP, O_RDONLY);
	dup2(file_def, STDIN);
	//close(file_def);
	dup2(save_out, STDOUT);
	close(save_out);
}

/* void	interrupt_here_document(int signal)
{
	(void)signal;
	errno = 130;
	write(1, "\n", 1);
	exit(130);
}

static int	create_temporary_file(void)
{
	int	fd;

	fd = open(FILE_TMP, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		printf("ERROOR\n");
	return (fd);
}

static	void	get_and_write_input(int tmp_fd, char *eof)
{
	char	*input;

	signal(SIGINT, interrupt_here_document);
	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			printf("ERROOR oi\n");
			close(tmp_fd);
			exit(0);
		}
		if (ft_strcmp(input, eof))
			ft_putendl_fd(input, tmp_fd);
		else
		{
			close(tmp_fd);
			free(input);
			break ;
		}
		free(input);
	}
	exit(0);
}

static void	clear_tmp_file_input(void)
{
	int		tmp_fd;

	tmp_fd = open(FILE_TMP, O_WRONLY | O_TRUNC, 0600);
	close(tmp_fd);
}

static void	make_tmp_file_input(void)
{
	int		tmp_fd;

	tmp_fd = open(FILE_TMP, O_RDONLY);
	unlink(FILE_TMP);
	dup2(tmp_fd, 0);
	close(tmp_fd);
}
 */
/* void	dr_here(char *eof, int *save_fd)
{
	int		tmp_fd;
	int		save_fd_out;
	int		pid;
	int		status;

	tmp_fd = create_temporary_file();
	if (tmp_fd == -1)
		return ;
	save_fd_out = dup(0);
	dup2(save_fd[1], STDOUT_FILENO);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		get_and_write_input(tmp_fd, eof);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		clear_tmp_file_input();
		errno = 130;
	}
	make_tmp_file_input();
	dup2(save_fd_out, STDOUT_FILENO);
	close(save_fd_out);
}
 */