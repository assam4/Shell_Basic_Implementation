/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:28:41 by saslanya          #+#    #+#             */
/*   Updated: 2025/04/19 12:28:43 by saslanya         ###   ########.fr       */
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
	if ((!prev || !next)
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

static bool	check_redirections(const t_list *tokens)
{
	t_token	*next;

	if (!tokens->next)
		return (false);
	next = (t_token *)tokens->next->content;
	if (!next || next->t_type != WORD
		|| !next->word || *(next->word) == '\0' || *(next->word) == '\n')
		return (false);
	else
		return (true);
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

bool	syntax_analyse(const t_list *tokens)
{
	const t_list	*prev;
	t_token			*t;
	int				sub_count;

	prev = NULL;
	sub_count = 0;
	while (tokens)
	{
		t = (t_token *)tokens->content;
		if (t->o_type == OP_SUBSHELL_OPEN || t->o_type == OP_SUBSHELL_CLOSE)
		{
			if (!check_subshell(prev, tokens, &sub_count))
				return (false);
		}
		else if ((t->t_type == OPERATION && !(check_operations(prev, tokens)))
			|| (t->t_type == REDIRECTION && !check_redirections(tokens)))
			return (error_message(prev, tokens), false);
		prev = tokens;
		tokens = tokens->next;
	}
	return (!sub_count);
}
