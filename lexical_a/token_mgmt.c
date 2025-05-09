/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_mgmt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:28:41 by saslanya          #+#    #+#             */
/*   Updated: 2025/04/19 12:28:43 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

bool	ft_isspace(const char *line)
{
	return (*line == ' ' || *line == '\t' || *line == '\n' || *line == '\r');
}

bool	is_operation(const char *line)
{
	if (*line == '&')
		return (true);
	if (*line == '(' || *line == ')')
		return (true);
	if (*line == '|')
		return (true);
	if (*line == ';')
		return (true);
	return (false);
}

bool	is_redirection(const char *line)
{
	return (*line == '<' || *line == '>');
}

void	token_free(void *data)
{
	t_token	*token;

	token = (t_token *)data;
	if (token->t_type == WORD)
		free(token->word);
	free(token);
}

bool	get_tokens(const char *line, t_list **tokens)
{
	while (*line)
	{
		if (ft_isspace(line) && ++line)
			continue ;
		else if (is_operation(line)
			&& !get_token(&line, tokens, set_op_token))
			return (ft_lstclear(tokens, token_free), false);
		else if (is_redirection(line)
			&& !get_token(&line, tokens, set_rd_token))
			return (ft_lstclear(tokens, token_free), false);
		else if (*line && !ft_isspace(line)
			&& !is_operation(line)
			&& !is_redirection(line)
			&& !get_token(&line, tokens, set_wd_token))
			return (ft_lstclear(tokens, token_free), false);
	}
	return (true);
}
