/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blossom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:12:16 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/07 21:27:44 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

static void	get_logic(t_list **prev, t_list *tokens)
{
	while (tokens && tokens->next)
	{
		if (((t_token *)tokens->content)->o_type == OP_SUBSHELL_OPEN)
			while (tokens && ((t_token *)tokens->next->content)->o_type != OP_SUBSHELL_CLOSE)
				tokens = tokens->next;
		if (tokens && (((t_token *)tokens->next->content)->o_type == OP_AND
			||((t_token *)tokens->next->content)->o_type == OP_OR))
			*prev = tokens;
		tokens = tokens->next;
	}
}
static void	get_pipe(t_list **prev, t_list *tokens)
{
	while (tokens && tokens->next)
	{
		if (((t_token *)tokens->content)->o_type == OP_SUBSHELL_OPEN)
			while (tokens && ((t_token *)tokens->next->content)->o_type != OP_SUBSHELL_CLOSE)
				tokens = tokens->next;
		if (tokens && (((t_token *)tokens->next->content)->o_type == OP_PIPE))
			*prev = tokens;
		tokens = tokens->next;
	}	
}

static bool	create_node(t_ast_node **node, t_list *tokens)
{
	*node = ft_calloc(1, sizeof(t_ast_node));
	if (!*node)
		return (false);
	tree_blossom(*node, tokens);
	return (true);
}

static bool	get_operator(t_ast_node *tree, t_list *tokens, void getter(t_list **, t_list *))
{
	t_list	*prev;

	prev = NULL;
	getter(&prev, tokens);
	if (!prev)
	{
		tree->token = ft_calloc(1, sizeof(t_token));
		if (!tree->token)
			return (false);
		tree->token->t_type = WORD;
		tree->cmd = tokens;
	}
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

void	tree_blossom(t_ast_node *tree, t_list *tokens)
{
	if (get_operator(tree, tokens, get_logic))
		return ;
	else if (get_operator(tree, tokens, get_pipe))
		return ;
	else if (tree->cmd && ((t_token *)tree->cmd->content)->o_type == OP_SUBSHELL_OPEN)
	{
		tree->token->t_type = OPERATION;
		tree->token->o_type = OP_SUBSHELL_OPEN;
		tree->cmd = tree->cmd->next;
		tree_blossom(tree, tree->cmd);
		tree->cmd = NULL;
	}
	return ;
}
