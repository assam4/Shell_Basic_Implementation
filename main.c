/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:08:23 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/13 19:37:59 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "tree.h"
#include "executor.h"

// ------------------------- ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ -------------------------

t_token *new_token(t_token_type t_type, t_operator_type o_type, char *word)
{
	t_token *token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->t_type = t_type;
	token->o_type = o_type;
	token->r_type = REDIR_NONE;
	token->word = word ? ft_strdup(word) : NULL;
	return (token);
}

t_list *add_token(t_list *lst, t_token_type t_type, t_operator_type o_type, char *word)
{
	t_token *token = new_token(t_type, o_type, word);
	t_list *node = ft_lstnew(token);
	if (!node)
		return NULL;
	if (!lst)
		return node;
	ft_lstadd_back(&lst, node);
	return lst;
}

// ------------------------- ФУНКЦИЯ ПЕЧАТИ ДЕРЕВА AST -------------------------

void	print_ast(t_ast_node *node, int depth)
{
	if (!node)
		return;

	// Print tree structure with branches
	for (int i = 0; i < depth; ++i)
		printf("│   ");
	printf("├── ");

	// Display node content based on type
	if (node->token->t_type == OPERATION)
	{
		if (node->token->o_type == OP_AND)
			printf("AND (&&)\n");
		else if (node->token->o_type == OP_OR)
			printf("OR (||)\n");
		else if (node->token->o_type == OP_PIPE)
			printf("PIPE (|)\n");
		else if (node->token->o_type == OP_SUBSHELL_OPEN)
			printf("SUBSHELL\n");
		else
			printf("OPERATION\n");
	}
	else if (node->token->t_type == WORD)
	{
		printf("COMMAND: ");
		t_list *cmd = node->cmd;
		while (cmd)
		{
			t_token *tok = (t_token *)cmd->content;
			printf("%s ", tok->word);
			cmd = cmd->next;
		}
		if (node->redir)
			printf("Redirs: ");
		t_list *tmp = node->redir;
		while (tmp)
		{
			if (((t_token *)tmp->content)->r_type == REDIR_IN) printf("<%s", ((t_token *)tmp->content)->word);
			else if (((t_token *)tmp->content)->r_type == REDIR_OUT) printf(">%s", ((t_token *)tmp->content)->word);
			else if (((t_token *)tmp->content)->r_type == REDIR_APPEND) printf(">>%s", ((t_token *)tmp->content)->word);
			else if (((t_token *)tmp->content)->r_type == REDIR_HERE_DOC) printf("<<%s", ((t_token *)tmp->content)->word);
			printf(" ");
			tmp = tmp->next;
		}

		printf("\n");
	}

	// Recurse into left and right children
	if (node->left || node->right)
	{
		print_ast(node->left, depth + 1);
		print_ast(node->right, depth + 1);
	}
}


// ------------------------------ ТЕСТ ------------------------------

int	main(int argc, char **argv, char **envp)
{
	t_list *tokens = NULL;

	if (argc < 2)
	{
		ft_putstr_fd("Usage: ./test \"your command\"\n", STDERR_FILENO);
		return (1);
	}

	if (!get_tokens(argv[1], &tokens)) {
		ft_putstr_fd("❌ Tokenization error\n", STDERR_FILENO);
		return (1);
	}

	if (!syntax_analyse(tokens)) {
		ft_putstr_fd("❌ Syntax error\n", STDERR_FILENO);
		ft_lstclear(&tokens, token_free);
		return (1);
	}
	else {
		ft_putstr_fd("✅ Syntax is correct\n", STDOUT_FILENO);
	}

	t_ast_node *tree = ft_calloc(1, sizeof(t_ast_node));
	tree_blossom(tree, tokens);

	printf("===== AST Tree =====\n");
	print_ast(tree, 0);
	printf("====================\n\n");

	// ✅ Вызов execute_node
	execute_node(tree, envp);

	tree_felling(&tree);
	return (0);
}

