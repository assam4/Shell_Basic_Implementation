/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 01:00:58 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/15 20:57:53 by saslanya         ###   ########.fr       */
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
	if (fd == -1)
		return (-1);
	return (fd);
}

static bool	open_redir(t_token *redir, t_ast_node *node)
{
	int	fd;

	if (!node->cmd)
		return (true);
	fd = open_file(redir);
	if (fd == -1)
		return (false);
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
		if (!open_redir(iter->content, node))
			return (false);
		iter = iter->next;
	}
	return (true);
}
