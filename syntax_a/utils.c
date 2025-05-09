/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:18:37 by saslanya          #+#    #+#             */
/*   Updated: 2025/05/10 12:48:12 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

static void	print_operation(t_token *current)
{
	if (current->o_type == OP_PIPE)
		ft_putstr_fd("|", STDERR_FILENO);
	else if (current->o_type == OP_AND)
		ft_putstr_fd("&&", STDERR_FILENO);
	else if (current->o_type == OP_BACKGROUND)
		ft_putstr_fd("&", STDERR_FILENO);
	else if (current->o_type == OP_OR)
		ft_putstr_fd("||", STDERR_FILENO);
	else if (current->o_type == OP_END)
		ft_putstr_fd(";", STDERR_FILENO);
	else if (current->o_type == OP_SUBSHELL_CLOSE)
		ft_putstr_fd(")", STDERR_FILENO);
	else if (current->o_type == OP_SUBSHELL_OPEN)
		ft_putstr_fd("(", STDERR_FILENO);
}

static void	print_redirection(t_token *current)
{
	if (current->r_type == REDIR_IN)
		ft_putstr_fd("<", STDERR_FILENO);
	else if (current->r_type == REDIR_OUT)
		ft_putstr_fd(">", STDERR_FILENO);
	else if (current->r_type == REDIR_APPEND)
		ft_putstr_fd(">>", STDERR_FILENO);
	else if (current->r_type == REDIR_HERE_DOC)
		ft_putstr_fd("<<", STDERR_FILENO);
}

static void	print_token(t_token *current)
{
	if (current->t_type == OPERATION)
		print_operation(current);
	else if (current->t_type == REDIRECTION)
		print_redirection(current);
	else if (current->t_type == WORD)
		ft_putstr_fd(current->word, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

static void	redir_error(const t_list *tokens)
{
	t_token	*current;

	current = (t_token *)tokens->content;
	if (!tokens->next)
	{
		ft_putstr_fd("newline'\n'", STDERR_FILENO);
		return ;
	}
	current = (t_token *)tokens->next->content;
	if (current->word && *(current->word) == '\n')
		ft_putstr_fd("newline'\n'", STDERR_FILENO);
	else
		print_token((t_token *)tokens->next->content);
}

void	error_message(const t_list *prev, const t_list *tokens)
{
	t_token	*current;

	current = (t_token *)tokens->content;
	ft_putstr_fd((char *)ERR_MESSAGE, STDERR_FILENO);
	if (prev && current->t_type == OPERATION && tokens->next
		&& ((t_token *)tokens->next->content)->t_type == OPERATION)
		print_token((t_token *)tokens->next->content);
	else if (current->t_type == OPERATION
		&& current->o_type != OP_SUBSHELL_OPEN
		&& current->o_type != OP_SUBSHELL_CLOSE)
		print_token(current);
	else if (current->t_type == REDIRECTION)
		redir_error(tokens);
	else
	{
		if (tokens->next)
			print_token((t_token *)tokens->next->content);
		else
			print_token((t_token *)tokens->content);
	}
}
