#include "token.h"
#include <stdio.h>

static void	print_token(t_token *token)
{
	if (token->t_type == WORD)
		printf("WORD: [%s]\n", token->word);
	else if (token->t_type == OPERATION)
	{
		printf("OPERATION: ");
		if (token->o_type == OP_AND) printf("AND\n");
		else if (token->o_type == OP_OR) printf("OR\n");
		else if (token->o_type == OP_PIPE) printf("PIPE\n");
		else if (token->o_type == OP_END) printf("END\n");
		else if (token->o_type == OP_SUBSHELL_OPEN) printf("SUBSHELL_OPEN\n");
		else if (token->o_type == OP_SUBSHELL_CLOSE) printf("SUBSHELL_CLOSE\n");
		else printf("UNKNOWN\n");
	}
	else if (token->t_type == REDIRECTION)
	{
		printf("REDIRECTION: ");
		if (token->r_type == REDIR_IN) printf("INPUT (<)\n");
		else if (token->r_type == REDIR_OUT) printf("OUTPUT (>)\n");
		else if (token->r_type == REDIR_APPEND) printf("APPEND (>>)\n");
		else if (token->r_type == REDIR_HERE_DOC) printf("HEREDOC (<<)\n");
		else printf("UNKNOWN\n");
	}
}

int	main(int argc, char **argv)
{
	t_list	*tokens = NULL;
	t_list	*node;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s \"command line\"\n", argv[0]);
		return (1);
	}
	if (!get_tokens(argv[1], &tokens))
	{
		fprintf(stderr, "Tokenization failed.\n");
		return (1);
	}
	node = tokens;
	while (node)
	{
		print_token((t_token *)node->content);
		node = node->next;
	}
	ft_lstclear(&tokens, token_free);
	return (0);
}

