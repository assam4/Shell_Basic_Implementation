/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 01:00:58 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/23 13:33:48 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	open_file(t_token *redir)
{
	int	fd;

	if (redir->r_type == REDIR_IN)
		fd = open(redir->word, O_RDONLY);
	else if (redir->r_type == REDIR_OUT)
		fd = open(redir->word, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	else if (redir->r_type == REDIR_APPEND)
		fd = open(redir->word, O_CREAT | O_WRONLY | O_APPEND, 0664);
	return (fd);
}

static bool	open_redir(t_token *redir)
{
	int	fd;

	fd = open_file(redir);
	if (fd == -1)
		return (print_error(redir->word, NULL, true), false);
	if ((redir->r_type == REDIR_IN)
		&& dup2(fd, STDIN_FILENO) == -1)
		return (close(fd), unlink(TMP_FILE), false);
	else if ((redir->r_type == REDIR_OUT || redir->r_type == REDIR_APPEND)
		&& dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), false);
	close(fd);
	return (true);
}

bool	set_redirs(t_ast_node *node)
{
	t_list	*iter;

	if (!node->redir)
		return (true);
	iter = node->redir;
	while (iter)
	{
		if (!open_redir(iter->content))
			return (false);
		iter = iter->next;
	}
	return (true);
}

void	child_process(int *fd, int stream)
{
	signal(SIGINT, SIG_DFL);
	if (stream == STDIN_FILENO)
		dup2(fd[0], STDIN_FILENO);
	else
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
}
