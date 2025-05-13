/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 01:00:58 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/14 02:35:31 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		++i;
	}
	return (0);
}

static void	here_doc_input(char *limiter)
{
	char	*str;
	int		fd;
	char	*lim;

	fd = open(TMP_FILE, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	lim = ft_strjoin(limiter, "\n");
	while (1)
	{
		ft_putstr_fd("> ", 1);
		str = get_next_line(0);
		if (!str || ft_strcmp(str, lim) == 0)
		{
			free(str);
			break ;
		}
		ft_putstr_fd(str, fd);
		free(str);
	}
	free(lim);
	close(fd);
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
	if (fd == -1)
		return (-1);
	return (fd);
}

static bool	open_redir(t_token *redir)
{
	int	fd;

	fd = open_file(redir);
	if (fd == -1)
		return (false);
	if (redir->r_type == REDIR_IN)
		dup2(fd, STDIN_FILENO);
	else if (redir->r_type == REDIR_OUT)
		dup2(fd, STDOUT_FILENO);
	else if (redir->r_type == REDIR_APPEND)
		dup2(fd, STDOUT_FILENO);
	else if (redir->r_type == REDIR_HERE_DOC)
	{
		here_doc_input(redir->word);
		fd = open(TMP_FILE, O_RDONLY);
		if (fd == -1)
			return (false);
		dup2(fd, STDIN_FILENO);
	}
	close(fd);
	unlink(TMP_FILE);
	return (true);
}

bool	set_redirs(t_ast_node *node)
{
	t_list	*iter;

	if (!node->redir)
		return (false);
	iter = node->redir;
	while (iter)
	{
		if (!open_redir(iter->content))
			return (false);
		iter = iter->next;
	}
	return (true);
}
