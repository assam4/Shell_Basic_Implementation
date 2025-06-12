/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:41:02 by saslanya          #+#    #+#             */
/*   Updated: 2025/06/12 23:32:58 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

static void	loop(const char *limiter, t_env *vars, int fd, int in_quotes)
{
	char	*line;

	while (true)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!in_quotes)
			process_env_expansion(&line, vars, true);
		if (!line)
		{
			print_warning((char *)limiter, vars);
			break ;
		}
		if (!ft_strncmp(line, limiter, ft_strlen(limiter) + 1))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
}

static int	here_doc_loop(const char *tmp_file
		, const char *limiter, t_env *vars)
{
	int		fd;
	bool	in_quotes;

	in_quotes = false;
	if (limiter[0] == '\'' || limiter[0] == '"')
		in_quotes = true;
	erase_quotes((char **)&limiter, false, false);
	if (!limiter)
		return (EXIT_FAILURE);
	fd = open(tmp_file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
		exit(EXIT_FAILURE);
	loop(limiter, vars, fd, in_quotes);
	close(fd);
	exit(EXIT_SUCCESS);
}

static bool	input_here_doc(char *tmp_file, char *limiter, t_env *vars)
{
	pid_t	process_id;
	int		status;

	signal(SIGINT, SIG_IGN);
	process_id = fork();
	if (process_id == -1)
		return (false);
	if (!process_id)
	{
		signal(SIGINT, SIG_DFL);
		here_doc_loop(tmp_file, limiter, vars);
		exit(EXIT_SUCCESS);
	}
	signal(SIGINT, handler);
	waitpid(process_id, &status, 0);
	set_exit_status(vars, status);
	return (!WIFSIGNALED(status)
		&& WIFEXITED(status) && !(WEXITSTATUS(status)));
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

bool	heredoc_exec(t_list *tokens, int i, t_env *vars)
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
	if (input_here_doc(fullname, limiter, vars))
	{
		tokens_update(tokens, fullname);
		return (free(limiter), true);
	}
	else
		return (free(fullname), free(limiter), false);
}
