/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 01:00:58 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/14 20:57:53 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	here_doc_input(char *limiter)
{
	char	*str;
	int		fd;
	char	*lim;

	fd = open(TMP_FILE, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
		return ;
	lim = ft_strjoin(limiter, "\n");
	if (!lim)
	{
		close(fd);
		return ;
	}
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		str = get_next_line(STDIN_FILENO);
		if (!str || !ft_strncmp(str, lim, ft_strlen(lim) + 1))
			break ;
		ft_putstr_fd(str, fd);
		free(str);
	}
	free(str);
	free(lim);
	close(fd);
}

static int	here_doc_fork(t_token *redir)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		here_doc_input(redir->word);
	waitpid(pid, &status, 0);
	return (WIFEXITED(status) && !(WEXITSTATUS(status)));
}

static int	open_file(t_token *redir)
{
	int	fd;

	if (redir->r_type == REDIR_IN)
		fd = open(redir->word, O_RDONLY);
	else if (redir->r_type == REDIR_OUT)
		fd = open(redir->word, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	else if (redir->r_type == REDIR_APPEND)
		fd = open(redir->word, O_CREAT | O_WRONLY | O_APPEND, 0664);
	else if(redir->r_type == REDIR_HERE_DOC)
		fd = open(TMP_FILE, O_RDONLY);
	if (fd == -1)
		return (-1);
	return (fd);
}

static bool	open_redir(t_token *redir, t_ast_node *node)
{
	int	fd;

	if (redir->r_type == REDIR_HERE_DOC && here_doc_fork(redir) != 1)
		return (false);
	if (!node->cmd)
		return (true);
	fd = open_file(redir);
	if (fd == -1)
		return (false);
	if ((redir->r_type == REDIR_IN || redir->r_type == REDIR_HERE_DOC)
		&& dup2(fd, STDIN_FILENO) == -1)
		return (close(fd), unlink(TMP_FILE), false);
	else if ((redir->r_type == REDIR_OUT || redir->r_type == REDIR_APPEND)
		&& dup2(fd, STDOUT_FILENO) == -1)
			return (close(fd), false);
	close(fd);
	if (redir->r_type == REDIR_HERE_DOC)
		unlink(TMP_FILE);
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
