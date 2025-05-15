/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:23:37 by saslanya          #+#    #+#             */
/*   Updated: 2025/05/15 14:33:09 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

void	content_swap(t_list *first, t_list *second)
{
	void	*tmp;

	tmp = first->content;
	first->content = second->content;
	second->content = tmp;
}

static bool	input_here_doc(char *tmp_file, char *limiter)
{
	int		fd;
	char	*line;

	if (!limiter)
		return (false);
	fd = open(tmp_file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
		return (free(tmp_file), free(limiter), false);
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (!ft_strncmp(line, limiter, ft_strlen(limiter) + 1))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
	close(fd);
	return (free(limiter), true);
}

static void	tokens_update(t_list *tokens, char *fd_name)
{
	t_list	*temp;

	temp = tokens->next;
	if (temp)
	{
		tokens->next = temp->next;
		temp->next = NULL;
		ft_lstclear(&temp, token_free);
	}
	((t_token *)tokens->content)->word = fd_name;
	((t_token *)tokens->content)->is_tmp = true;
	((t_token *)tokens->content)->t_type = WORD;
	((t_token *)tokens->content)->r_type = REDIR_NONE;
}

bool	heredoc_exec(t_list *tokens, int i)
{
	char	*fullname;
	char	*i_str;
	char	*limiter;

	i_str = ft_itoa(i);
	if (!i_str)
		return (false);
	fullname = ft_strjoin(TMP_DIR, i_str);
	free(i_str);
	if (!fullname)
		return (false);
	limiter = ft_strjoin(((t_token *)tokens->next->content)->word, "\n");
	if (!limiter)
		return (free(fullname), false);
	if (input_here_doc(fullname, limiter))
	{
		tokens_update(tokens, fullname);
		return (true);
	}
	else
		return (free(fullname), false);
}
