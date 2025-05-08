/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:28:41 by saslanya          #+#    #+#             */
/*   Updated: 2025/05/08 12:48:43 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

static void	jump_subshells(t_list **tokens)
{
	t_list	*iter;
	int		counter;

	counter = 0;
	iter = *tokens;
	if (((t_token *)iter->content)->o_type == OP_SUBSHELL_OPEN)
		++counter;
	while (iter && counter)
	{
		if (((t_token *)iter->content)->o_type == OP_SUBSHELL_OPEN)
			++counter;
		else if (((t_token *)iter->content)->o_type == OP_SUBSHELL_CLOSE)
			--counter;
		iter = iter->next;
	}
	*tokens = iter;
}

void	get_logic(t_list **prev, t_list *tokens)
{
	while (tokens && tokens->next)
	{
		if (((t_token *)tokens->content)->o_type == OP_SUBSHELL_OPEN)
			jump_subshells(&tokens);
		if (!tokens)
			return ;
		if ((((t_token *)tokens->next->content)->o_type == OP_AND
			|| ((t_token *)tokens->next->content)->o_type == OP_OR))
			*prev = tokens;
		tokens = tokens->next;
	}
}

void	get_pipe(t_list **prev, t_list *tokens)
{
	while (tokens && tokens->next)
	{
		if (((t_token *)tokens->content)->o_type == OP_SUBSHELL_OPEN)
			jump_subshells(&tokens);
		if (!tokens)
			return ;
		if (((t_token *)tokens->next->content)->o_type == OP_PIPE)
			*prev = tokens;
		tokens = tokens->next;
	}
}

static bool	create_node(t_ast_node **node, t_list *tokens)
{
	if (!node || *node)
		return (false);
	*node = ft_calloc(1, sizeof(t_ast_node));
	if (!*node)
		return (false);
	tree_blossom(*node, tokens);
	return (true);
}

bool	get_operator(t_ast_node *tree
			, t_list *tokens
			, void getter(t_list **, t_list *))
{
	t_list	*prev;

	prev = NULL;
	getter(&prev, tokens);
	if (!prev)
		return (false);
	else
	{
		tree->token = (t_token *)prev->next->content;
		if (!create_node(&(tree->right), prev->next->next))
			return (false);
		prev->next = NULL;
		if (!create_node(&(tree->left), tokens))
			return (false);
	}
	return (true);
}
