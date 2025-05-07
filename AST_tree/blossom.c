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

void	tree_blossom(t_ast_node *tree, t_list *tokens)
{
	if (get_operator(tree, tokens, get_logic))
		return ;
	if (get_operator(tree, tokens, get_pipe))
		return ;
	else if (tree->cmd
		&& ((t_token *)tree->cmd->content)->o_type == OP_SUBSHELL_OPEN)
	{
		tree->token->t_type = OPERATION;
		tree->token->o_type = OP_SUBSHELL_OPEN;
		tree->cmd = tree->cmd->next;
		tree_blossom(tree, tree->cmd);
		tree->cmd = NULL;
	}
	else
	{
		tree->token = ft_calloc(1, sizeof(t_token));
		if (!tree->token)
			return ;
		tree->token->t_type = WORD;
		tree->cmd = tokens;
	}
}
