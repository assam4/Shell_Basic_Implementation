/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blossom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:42:58 by saslanya          #+#    #+#             */
/*   Updated: 2025/05/16 09:43:00 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

void	tree_felling(t_ast_node **tree)
{
	t_list		*tmp;

	token_free((*tree)->token);
	if ((*tree)->left)
		tree_felling(&(*tree)->left);
	(*tree)->left = NULL;
	if ((*tree)->right)
		tree_felling(&(*tree)->right);
	(*tree)->right = NULL;
	if ((*tree)->cmd)
		ft_lstclear(&(*tree)->cmd, token_free);
	(*tree)->cmd = NULL;
	if ((*tree)->redir)
	{
		tmp = (*tree)->redir;
		while (tmp)
		{
			free(((t_token *)tmp->content)->word);
			tmp = tmp->next;
		}
		ft_lstclear(&(*tree)->redir, token_free);
		(*tree)->redir = NULL;
	}
	free(*tree);
	*tree = NULL;
}

static t_list	*get_sub_content(t_ast_node *tree, t_list **tokens)
{
	t_list	*temp;
	int		counter;

	counter = 1;
	tree->token = (t_token *)(*tokens)->content;
	temp = *tokens;
	*tokens = (*tokens)->next;
	free(temp);
	temp = *tokens;
	while ((*tokens)->next)
	{
		if (((t_token *)(*tokens)->next->content)->o_type
			== OP_SUBSHELL_OPEN)
			++counter;
		else if (((t_token *)(*tokens)->next->content)->o_type
			== OP_SUBSHELL_CLOSE)
			--counter;
		if (!counter)
			break ;
		*tokens = (*tokens)->next;
	}
	return (temp);
}

static int	get_subshell(t_ast_node *tree, t_list *tokens)
{
	t_list	*sub_content;

	if (((t_token *)tokens->content)->o_type == OP_SUBSHELL_OPEN)
	{
		sub_content = get_sub_content(tree, &tokens);
		if (!create_node(&(tree->left), sub_content))
			return (ENOMEM);
		return (true);
	}
	else
		return (false);
}

int	tree_blossom(t_ast_node *tree, t_list *tokens)
{
	int	status;

	status = get_operator(tree, tokens, get_logic);
	if (status)
		return (status);
	status = get_operator(tree, tokens, get_pipe);
	if (status)
		return (status);
	status = get_subshell(tree, tokens);
	if (status)
		return (status);
	else
	{
		tree->token = ft_calloc(1, sizeof(t_token));
		if (!tree->token)
			return (ENOMEM);
		tree->token->t_type = WORD;
		token_spliter(tree, tokens);
	}
	return (true);
}
