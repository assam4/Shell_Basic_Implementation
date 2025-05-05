#include "syntax.h"
// need to add redirections 
void	error_message(const char *message, const t_token *current)
{
	ft_putstr_fd(message, STDERR_FILENO);
	if (current->t_type == OPERATION)
	{
		if (current->o_type == OP_PIPE)
			ft_putstr_fd("|\'\n", STDERR_FILENO);
		else if (current->o_type == OP_AND)
			ft_putstr_fd("&&\'\n", STDERR_FILENO);
		else if (current->o_type == OP_OR)
			ft_putstr_fd("||\'\n", STDERR_FILENO);
		else if (current->o_type == OP_END)
			ft_putstr_fd(";\'\n", STDERR_FILENO);
		else if (current->o_type == OP_SUBSHELL_CLOSE)
			ft_putstr_fd(")\'\n", STDERR_FILENO);
	}
}

bool	check_operations(t_list *prev_l, t_list *tokens)
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
	if (((!prev && current->o_type != OP_SUBSHELL_OPEN) || !next)
		|| (prev
			&& ((prev->content->t_type == OPERATION
					&& prev->o_type != OP_SUBSHELL_CLOSE)
				|| prev->t_type != WORD))
		|| (next
			&& (next->t_type == OPERATION
				&& next->o_type != OP_SUBSHELL_OPEN)))
		return (false);
	else
		return (true);
}

// need think about subshells count handling and need to add redirection errors
bool	syntax_analyse(const t_list *tokens)
{
	t_list	*prev;
	t_token	*token;
	int		sub_count;

	prev = NULL;
	sub_count = 0;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (token->t_type == OPERATION && !(check_operations(prev, tokens)))
			return (error_message(UN_TOKEN, token), false);
		if (token->o_type == OP_SUBSHELL_OPEN)
			++sub_count;
		else if (token->o_type == OP_SUBSHELL_CLOSE && --sub_count < 0)
			return (error_message(UN_TOKEN, token), false);
		prev = tokens;
		tokens = tokens->next;
	}
	return (true);
}
