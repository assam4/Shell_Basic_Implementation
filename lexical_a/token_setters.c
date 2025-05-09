/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_setters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:30:06 by saslanya          #+#    #+#             */
/*   Updated: 2025/05/09 17:34:39 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	set_op_token(const char **line, t_token *token)
{
	token->t_type = OPERATION;
	if (**line == '&' && *(*line + 1) == '&')
		token->o_type = OP_AND;
	else if (**line == '&')
		token->o_type = OP_BACKGROUND;
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

static	int	word_len(const char *line)
{
	int		i;
	bool	single_quotes;
	bool	double_quotes;

	i = 0;
	single_quotes = false;
	double_quotes = false;
	while (line[i] && (single_quotes
			|| double_quotes
			|| (!ft_isspace(line + i)
				&& !is_operation(line + i)
				&& !is_redirection(line + i))))
	{
		if (line[i] == '\'' && !double_quotes)
			single_quotes = !single_quotes;
		else if (line[i] == '\"' && !single_quotes)
			double_quotes = !double_quotes;
		++i;
	}
	return (i);
}

void	set_wd_token(const char **line, t_token *token)
{
	int			i;
	const char	*str;

	str = *line;
	i = word_len(str);
	token->t_type = WORD;
	token->word = ft_calloc(i + 1, sizeof(char));
	if (!token->word)
		return ;
	ft_strlcpy(token->word, str, i + 1);
	(*line) += i;
}

bool	get_token(const char **line, t_list **tokens,
		void (*setter)(const char **line, t_token *))
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
