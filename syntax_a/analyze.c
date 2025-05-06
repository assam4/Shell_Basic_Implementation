#include "syntax.h"

static void	print_token_str(t_token *current)
{
	if (current->o_type == OP_PIPE)
		ft_putstr_fd("|'\n", STDERR_FILENO);
	else if (current->o_type == OP_AND)
		ft_putstr_fd("&&'\n", STDERR_FILENO);
	else if (current->o_type == OP_OR)
		ft_putstr_fd("||'\n", STDERR_FILENO);
	else if (current->o_type == OP_END)
		ft_putstr_fd(";'\n", STDERR_FILENO);
	else if (current->o_type == OP_SUBSHELL_CLOSE)
		ft_putstr_fd(")'\n", STDERR_FILENO);
	else if (current->o_type == OP_SUBSHELL_OPEN)
		ft_putstr_fd("('\n", STDERR_FILENO);
	else if (current->r_type == REDIR_IN)
		ft_putstr_fd("<'\n", STDERR_FILENO);
	else if (current->r_type == REDIR_OUT)
		ft_putstr_fd(">'\n", STDERR_FILENO);
	else if (current->r_type == REDIR_APPEND)
		ft_putstr_fd(">>'\n", STDERR_FILENO);
	else if (current->r_type == REDIR_HERE_DOC)
		ft_putstr_fd("<<'\n", STDERR_FILENO);
}

static void	error_message(const t_list *tokens)
{
	t_token	*current;

	current = (t_token *)tokens->content;
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	if (current->t_type == OPERATION
		&& tokens->next
		&& ((t_token *)tokens->next->content)->t_type == OPERATION)
		print_token_str((t_token *)tokens->next->content);
	else if (current->t_type == OPERATION)
		print_token_str(current);
	else if (current->t_type == REDIRECTION)
	{
		if (!tokens->next)
		{
			ft_putstr_fd("newline'\n'", STDERR_FILENO);
			return ;
		}
		current = (t_token *)tokens->next->content;
		if (current->word && *(current->word) == '\n')
			ft_putstr_fd("newline'\n'", STDERR_FILENO);
		else
			print_token_str((t_token *)tokens->next->content);
	}
}

static bool	check_operations(const t_list *prev_l, const t_list *tokens)
{
	t_token	*prev;
	t_token	*current;
	t_token	*next;

	prev = NULL;
	next = NULL;
	if (prev_l)
		prev = (t_token *)prev_l->content;
	current = (t_token *)tokens->content;
	if (tokens->next)
		next = (t_token *)tokens->next->content;
	if ((!prev && current->o_type != OP_SUBSHELL_OPEN)
		|| (next && next->o_type == OP_SUBSHELL_CLOSE)
		|| (prev && prev->t_type == OPERATION
			&& prev->o_type != OP_SUBSHELL_CLOSE
			&& prev->o_type != OP_SUBSHELL_OPEN)
		|| (prev && prev->t_type == REDIRECTION)
		|| (next
			&& (next->t_type == OPERATION
				&& next->o_type != OP_SUBSHELL_OPEN)))
		return (false);
	else
		return (true);
}

static bool	check_redirections(const t_list *tokens)
{
	t_token	*next;

	if (!tokens->next)
		return (false);
	next = (t_token *)tokens->next->content;
	if (next->t_type != WORD
		|| (!next->word || (*(next->word) == '\0' || *(next->word) == '\n')))
		return (false);
	else
		return (true);
}

// need think about subshells count handling and need to add redirection errors
bool	syntax_analyse(const t_list *tokens)
{
	const t_list	*prev;
	t_token			*token;
	int				sub_count;

	prev = NULL;
	sub_count = 0;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		if ((token->t_type == OPERATION && !(check_operations(prev, tokens)))
			|| (token->o_type == OP_SUBSHELL_CLOSE && --sub_count < 0)
			|| (token->t_type == REDIRECTION && !check_redirections(tokens)))
			return (error_message(tokens), false);
		if (token->o_type == OP_SUBSHELL_OPEN)
			++sub_count;
		prev = tokens;
		tokens = tokens->next;
	}
	return (true);
}
