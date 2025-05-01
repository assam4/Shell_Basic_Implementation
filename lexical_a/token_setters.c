#include "token.h"

void	set_op_token(const char **line, t_token *token)
{
	token->t_type = OPERATION;
	if (**line == '&' && *(*line + 1) == '&')
		token->o_type = OP_AND;
	else if (**line == '|' && *(*line + 1) == '|')
		token->o_type = OP_OR;
	else if (**line == '|')
		token->o_type = OP_PIPE;
	else if (**line == '(')
		token->o_type = OP_SUBSHELL_OPEN;
	else if (**line == ')')
		token->o_type = OP_SUBSHELL_CLOSE;
	else if (**line == ';')
		token->o_type = OP_END;
	if (token->o_type == OP_AND || token->o_type == OP_OR)
		(*line) += 2;
	else
		++(*line);
}

void	set_rd_token(const char **line, t_token *token)
{
	token->t_type = REDIRECTION;
	if (**line == '<' && *(*line + 1) == '<')
		token->r_type = REDIR_HERE_DOC;
	else if (**line == '>' && *(*line + 1) == '>')
		token->r_type = REDIR_APPEND;
	else if (**line == '<')
		token->r_type = REDIR_IN;
	else if (**line == '>')
		token->r_type = REDIR_OUT;
	if (token->r_type == REDIR_HERE_DOC
		|| token->r_type == REDIR_APPEND)
		(*line) += 2;
	else
		++(*line);
}

void	set_wd_token(const char **line, t_token *token)
{
	int			i;
	const char	*str;

	i = 0;
	str = *line;
	while (str[i]
		&& !ft_isspace(str + i)
		&& !is_operation(str + i)
		&& !is_redirection(str + i))
		++i;
	token->t_type = WORD;
	token->word = ft_calloc(i + 1, sizeof(char));
	if (!token->word)
		return ;
	ft_strlcpy(token->word, str, i + 1);
	(*line) += i;
}

bool	get_token(const char **line, t_list **tokens
		, void (*setter)(const char **line, t_token *))
{
	t_list	*new_item;
	t_token	*token;

	new_item = ft_calloc(1, sizeof(t_list));
	if (!new_item)
		return (false);
	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (free(new_item), false);
	setter(line, token);
	if (token->t_type == WORD && !token->word)
		return (free(new_item), free(token), false);
	new_item->content = token;
	ft_lstadd_back(tokens, new_item);
	return (true);
}
