/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarreir <nbarreir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:45:16 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/10 04:36:55 by nbarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	create_mr_temporary_file(void)
{
	int	file_fd;

	file_fd = open(FILE_TMP, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (file_fd == -1)
		ft_putendl_fd("Redirect error.", 2);
	return (file_fd);
}

void	here_doc_loop(int file_tmp, char *eof)
{
	char	*tmp;

	while (1)
	{
		tmp = readline("> ");
		if (!tmp)
		{
			ft_putendl_fd("Temporary file error.", 2);
			close(file_tmp);
			exit(0);
		}
		if (tmp)
		{
			if (ft_strcmp(tmp, eof))
				ft_putendl_fd(tmp, file_tmp);
			if (!ft_strcmp(tmp, eof))
			{
				free(tmp);
				close(file_tmp);
				break ;
			}
		}
		free(tmp);
	}
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
	int	file_tmp;
	int	status;
	int	save_out;
	int	pid;

	save_out = dup(STDOUT);
	dup2(save_fd[0], STDIN);
	dup2(save_fd[1], STDOUT);
	file_tmp = create_mr_temporary_file();
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, interrupt_here_document);
		here_doc_loop(file_tmp, eof);
		exit(errno);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		errno = WIFEXITED(status);
	file_tmp = open(FILE_TMP, O_RDONLY);
	dup2(file_tmp, STDIN);
	dup2(save_out, STDOUT);
	close(save_out);
}
