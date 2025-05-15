/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_optimize.c                                     :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:42:23 by saslanya          #+#    #+#             */
/*   Updated: 2025/05/15 14:53:09 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

static bool	check_situation(t_token *current, t_token *next, t_list **tokens)
{
	t_list	*temp;

	if (current->is_tmp && !next)
		return (ft_lstclear(tokens, token_free), false);
	if (current->is_tmp && next
		&& next->t_type == WORD && !next->is_tmp)
		return (content_swap(*tokens, (*tokens)->next), false);
	if (current->is_tmp && next
		&& next->t_type == WORD && next->is_tmp)
	{
		temp = *tokens;
		*tokens = (*tokens)->next;
		ft_lstdelone(temp, token_free);
		return (true);
	}
	return (false);
}

static bool	head_optimize(t_list **tokens)
{
	t_token	*current;
	t_token	*next;

	while (*tokens)
	{
		current = (t_token *)(*tokens)->content;
		if ((*tokens)->next)
			next = (t_token *)(*tokens)->next->content;
		else
			next = NULL;
		if (!check_situation(current, next, tokens))
			break ;
	}
	return (true);
}

void	hdoc_destroy(t_list *tokens)
{
	t_list	*tmp;

	tmp = tokens->next;
	tokens->next = tokens->next->next;
	ft_lstdelone(tmp, token_free);
}

void	optimize_loop(t_list *tokens)
{
	t_token	*arr[3];

	while (tokens->next)
	{
		arr[0] = (t_token *)tokens->content;
		arr[1] = (t_token *)tokens->next->content;
		if (arr[1]->is_tmp && arr[0]->t_type != WORD)
		{
			if (tokens->next->next)
			{
				arr[2] = (t_token *)tokens->next->next->content;
				if (arr[2]->t_type == WORD && !arr[2]->is_tmp)
					content_swap(tokens->next, tokens->next->next);
				else if (arr[2]->t_type == WORD && arr[2]->is_tmp)
				{
					hdoc_destroy(tokens);
					continue ;
				}
			}
			else
				ft_lstclear(&tokens->next, token_free);
		}
		tokens = tokens->next;
	}
}

void	optimize_heredoc(t_list	**tokens)
{
	t_list	*iter;

	head_optimize(tokens);
	if (*tokens)
		iter = *tokens;
	else
		return ;
	optimize_loop(iter);
}
