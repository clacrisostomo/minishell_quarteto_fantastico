/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfico-vi <cfico-vi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 22:53:24 by nbarreir          #+#    #+#             */
/*   Updated: 2021/12/28 12:20:45 by cfico-vi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_mr_temporary_file(void)
{
	int	file_fd;

	file_fd = open(FILE_TMP, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (file_fd == -1)
		ft_putendl_fd("Redirect error.", 2);
	return (file_fd);
}

static void	hr_doc_child_exit(char **cmd, char **old_cmd)
{
	ft_free_split(cmd);
	ft_free_split(old_cmd);
	free_n_exit();
}

static void	here_doc_loop(int file_tmp, char **cmd, int i, char **old_cmd)
{
	char	*tmp;

	while (1)
	{
		tmp = readline("> ");
		if (!tmp)
		{
			ft_putendl_fd("Temporary file error.", 2);
			close(file_tmp);
			hr_doc_child_exit(cmd, old_cmd);
		}
		if (tmp)
		{
			if (ft_strcmp(tmp, cmd[i + 1]))
				ft_putendl_fd(tmp, file_tmp);
			if (!ft_strcmp(tmp, cmd[i + 1]))
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
	free_n_exit();
}

void	dr_here(char **cmd, int i, int *save_fd, char **old_cmd)
{
	int		file_tmp;
	int		status;
	int		save_out;
	int		pid;

	save_out = dup(STDOUT);
	dup2(save_fd[0], STDIN);
	file_tmp = create_mr_temporary_file();
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, interrupt_here_document);
		here_doc_loop(file_tmp, cmd, i, old_cmd);
		hr_doc_child_exit(cmd, old_cmd);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		errno = WIFEXITED(status);
	file_tmp = open(FILE_TMP, O_RDONLY);
	dup2(file_tmp, STDIN);
	dup2(save_out, STDOUT);
	close(save_out);
}
