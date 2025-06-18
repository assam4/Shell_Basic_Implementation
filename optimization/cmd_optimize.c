/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_optimize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:41:32 by aadyan            #+#    #+#             */
/*   Updated: 2025/06/18 12:34:49 by saslanya         ###   ########.fr       */
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

bool	erase_hdocs(t_list *tokens, t_list *temp, t_token **arr)
{
	if (arr[0]->t_type == WORD && arr[1]->is_tmp)
	{
		free(arr[0]->input_file);
		arr[0]->input_file = arr[1]->word;
		free(arr[1]);
		temp = tokens->next;
		tokens->next = temp->next;
		return (free(temp), true);
	}
	else if (arr[1]->is_tmp && arr[2]
		&& arr[2]->t_type == WORD && !arr[2]->is_tmp)
	{
		content_swap(tokens->next, tokens->next->next);
		free(arr[1]->input_file);
		arr[1]->input_file = arr[2]->word;
		free(arr[2]);
		temp = tokens->next->next;
		tokens->next->next = temp->next->next->next;
		return (free(temp), true);
	}
	else
		return (false);
}
