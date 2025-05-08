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

static bool	get_subshell(t_ast_node *tree, t_list *tokens)
{
	t_list	*temp;
	int	counter;

	temp = NULL;
	if (((t_token *)tokens->content)->o_type == OP_SUBSHELL_OPEN)
	{
		counter = 1;
		tree->token = (t_token *)tokens->content;
		temp = tokens;
		tokens = tokens->next;
		free(temp);
		temp = tokens;
		while (tokens->next)
		{
			if (((t_token *)tokens->next->content)->o_type
				== OP_SUBSHELL_OPEN)
				++counter;
			else if (((t_token *)tokens->next->content)->o_type
				== OP_SUBSHELL_CLOSE)
				--counter;
			if (!counter)
				break ;
			else
				tokens = tokens->next;
		}
		ft_lstclear(&(tokens->next), token_free);
		tokens->next = NULL;
		if (!create_node(&(tree->left), temp))
			return (false);
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
	else if (get_subshell(tree, tokens))
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
