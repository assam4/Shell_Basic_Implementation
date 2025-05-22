/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:40:46 by saslanya          #+#    #+#             */
/*   Updated: 2025/05/22 17:42:50 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

static bool	check_operations(const t_list *prev_l, const t_list *tokens)
{
	t_token	*prev;
	t_token	*next;

	prev = NULL;
	next = NULL;
	if (prev_l)
		prev = (t_token *)prev_l->content;
	if (tokens->next)
		next = (t_token *)tokens->next->content;
	if ((!prev)
		|| ((t_token *)prev_l->next->content)->o_type == OP_END
		|| ((t_token *)prev_l->next->content)->o_type == OP_BACKGROUND
		|| (next && next->t_type == OPERATION
			&& next->o_type != OP_SUBSHELL_OPEN)
		|| (prev && prev->t_type == OPERATION
			&& prev->o_type != OP_SUBSHELL_CLOSE)
		|| (prev && prev->t_type == REDIRECTION))
		return (false);
	else
		return (true);
}

static bool	operations_check_loop(const t_list *tokens)
{
	const t_list	*prev;
	t_token			*token;

	prev = NULL;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (token->t_type == OPERATION)
		{
			if (token->o_type != OP_SUBSHELL_OPEN
				&& token->o_type != OP_SUBSHELL_CLOSE)
				if (!check_operations(prev, tokens))
					return (error_message(prev, tokens), false);
		}
		prev = tokens;
		tokens = tokens->next;
	}
	return (true);
}

static bool	check_redirections(t_list *tokens, int i)
{
	t_token	*next;

	if (!tokens || !tokens->next)
		return (false);
	next = (t_token *)tokens->next->content;
	if (!next || next->t_type != WORD
		|| !next->word || *(next->word) == '\0' || *(next->word) == '\n')
		return (false);
	else
	{
		if (((t_token *)tokens->content)->r_type == REDIR_HERE_DOC)
			return (heredoc_exec(tokens, i));
		else
			return (true);
	}
}

bool	check_subshell(const t_list *prev, const t_list *tokens, int *count)
{
	t_token	*t;

	t = (t_token *)tokens->content;
	if (t->o_type == OP_SUBSHELL_OPEN)
	{
		if (prev && ((t_token *)prev->content)->t_type == WORD)
			return (error_message(NULL, tokens), false);
		++(*count);
		return (true);
	}
	else if (t->o_type == OP_SUBSHELL_CLOSE)
	{
		if (prev && ((t_token *)prev->content)->o_type == OP_SUBSHELL_OPEN)
			return (error_message(prev, prev), false);
		if (tokens->next
			&& ((t_token *)tokens->next->content)->t_type == WORD)
			return (error_message(NULL, tokens), false);
		if (--(*count) < 0)
			return (error_message(prev, tokens), false);
		return (true);
	}
	return (false);
}

bool	syntax_analyse(t_list *tokens)
{
	const t_list	*prev;
	t_token			*t;
	int				sub_count;
	int				i;

	prev = NULL;
	sub_count = 0;
	i = 0;
	if (!operations_check_loop(tokens))
		return (false);
	while (tokens)
	{
		t = (t_token *)tokens->content;
		if (t->o_type == OP_SUBSHELL_OPEN || t->o_type == OP_SUBSHELL_CLOSE)
		{
			if (!check_subshell(prev, tokens, &sub_count))
				return (false);
		}
		else if (t->t_type == REDIRECTION && !check_redirections(tokens, i++))
			return (error_message(tokens, tokens), false);
		prev = tokens;
		tokens = tokens->next;
	}
	return (sub_count >= 0);
}
