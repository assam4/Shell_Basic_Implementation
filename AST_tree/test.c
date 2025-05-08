#include <stdio.h>
#include <string.h>
#include "tree.h"

// ------------------------- ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ -------------------------

t_token *new_token(t_token_type t_type, t_operator_type o_type, const char *word)
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

t_list *add_token(t_list *lst, t_token_type t_type, t_operator_type o_type, const char *word)
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
		return ;
	for (int i = 0; i < depth; ++i)
		printf("  ");

	if (node->token->t_type == OPERATION)
	{
		if (node->token->o_type == OP_AND)
			printf("&&\n");
		else if (node->token->o_type == OP_OR)
			printf("||\n");
		else if (node->token->o_type == OP_PIPE)
			printf("|\n");
		else if (node->token->o_type == OP_SUBSHELL_OPEN)
			printf("SUBSHELL\n");
		else
			printf("OPERATION\n");
	}
	else if (node->token->t_type == WORD)
	{
		t_list *cmd = node->cmd;
		while (cmd)
		{
			t_token *tok = (t_token *)cmd->content;
			printf("%s ", tok->word);
			cmd = cmd->next;
		}
		printf("\n");
	}

	print_ast(node->left, depth + 1);
	print_ast(node->right, depth + 1);
}

// ------------------------------ ТЕСТ ------------------------------

int	main(void)
{
	 char input[1024];
    t_list *tokens = NULL;

    // Read command from stdin
    printf("Enter a command: ");
    if (!fgets(input, sizeof(input), stdin))
        return (1);

    // Remove the newline character from the end of the string
    input[strcspn(input, "\n")] = '\0';

    // Tokenization
    if (!get_tokens(input, &tokens)) {
        ft_putstr_fd("❌ Tokenization error\n", STDERR_FILENO);
        return (1);
    }

    // Syntax analysis
    if (!syntax_analyse(tokens)) {
        ft_putstr_fd("❌ Syntax error\n", STDERR_FILENO);
    } else {
        ft_putstr_fd("✅ Syntax is correct\n", STDOUT_FILENO);
    }

/*
	// Пример: echo hello && ls | wc
	tokens = add_token(tokens, WORD, OP_NONE, "echo");
	tokens = add_token(tokens, WORD, OP_NONE, "hello");
	tokens = add_token(tokens, OPERATION, OP_AND, NULL);
	tokens = add_token(tokens, WORD, OP_NONE, "ls");
	tokens = add_token(tokens, OPERATION, OP_PIPE, NULL);
	tokens = add_token(tokens, WORD, OP_NONE, "wc");
*/
	t_ast_node *tree = ft_calloc(1, sizeof(t_ast_node));
	tree_blossom(tree, tokens);

	printf("===== AST Tree =====\n");
	print_ast(tree, 0);

	return (0);
}

