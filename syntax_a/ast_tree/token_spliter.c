/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_spliter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:41:32 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/13 20:41:33 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

static void	word_spliter(t_ast_node *tree, t_list **tokens)
{
	t_list	*temp;

	temp = *tokens;
	*tokens = (*tokens)->next;
	temp->next = NULL;
	ft_lstadd_back(&tree->cmd, temp);
}

static void	redirection_spliter(t_ast_node *tree, t_list **tokens)
{
	t_list	*temp;

	temp = *tokens;
	*tokens = (*tokens)->next;
	temp->next = NULL;
	ft_lstadd_back(&tree->redir, temp);
	((t_token *)temp->content)->word
		= ((t_token *)(*tokens)->content)->word;
	temp = *tokens;
	*tokens = (*tokens)->next;
	free(temp->content);
	free(temp);
}

static void	pair_setter(t_token **current, t_token **next, t_list *tokens)
{
	*current = (t_token *)(tokens)->content;
	if (tokens->next)
		*next = (t_token *)(tokens)->next->content;
	else
		*next = NULL;
}

static void	optimize_heredoc(t_list **tokens)
{
	t_token	*current;
	t_token	*next;
	t_list	*start;

	start = *tokens;
	while (*tokens)
	{
		pair_setter(&current, &next, *tokens);
		if (current->is_tmp)
		{
			if (!next || next->is_tmp || next->t_type != WORD)
			{
				ft_lstclear(tokens, token_free);
				return ;
			}
			else
			{
				token_swap(*tokens, (*tokens)->next);
				*tokens = (*tokens)->next;
			}
		}
		*tokens = (*tokens)->next;
	}
	*tokens = start;
}

void	token_spliter(t_ast_node *tree, t_list *tokens)
{
	t_list	*temp;

	while (tokens)
		if (((t_token *)tokens->content)->t_type == WORD)
			word_spliter(tree, &tokens);
	else if (((t_token *)tokens->content)->t_type == REDIRECTION)
		redirection_spliter(tree, &tokens);
	else
	{
		temp = tokens;
		tokens = tokens->next;
		if (((t_token *)temp->content)->o_type == OP_SUBSHELL_CLOSE)
		{
			token_free(temp->content);
			free(temp);
		}
	}
	optimize_heredoc(&(tree->cmd));
}
