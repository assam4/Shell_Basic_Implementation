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

static bool	get_subshell(t_ast_node *tree)
{
	t_list	*temp;
	int	counter;

	temp = NULL;
	if (tree->cmd
		&& ((t_token *)tree->cmd->content)->o_type == OP_SUBSHELL_OPEN)
	{
		counter = 1;
		tree->token = (t_token *)tree->cmd->content;
		temp = tree->cmd;
		tree->cmd = tree->cmd->next;
		free(temp);
		temp = tree->cmd;
		while (tree->cmd->next)
		{
			if (((t_token *)tree->cmd->next->content)->o_type
				== OP_SUBSHELL_OPEN)
				++counter;
			else if (((t_token *)tree->cmd->next->content)->o_type
				== OP_SUBSHELL_CLOSE)
				--counter;
			if (!counter)
				break ;
			else
				tree->cmd = tree->cmd->next;
		}
		ft_lstclear(&(tree->cmd->next), token_free);
		tree->cmd->next = NULL;
		tree_blossom(tree, temp);
		tree->cmd = NULL;
		return (true);
	}
	else
		return (false);
}
	

void	tree_blossom(t_ast_node *tree, t_list *tokens)
{
	if (get_operator(tree, tokens, get_logic))
		return ;
	else if (get_operator(tree, tokens, get_pipe))
		return ;
	else if (get_subshell(tree))
		return ;
	else
	{
		tree->token = ft_calloc(1, sizeof(t_token));
		if (!tree->token)
			return ;
		tree->token->t_type = WORD;
		tree->cmd = tokens;
	}
}
