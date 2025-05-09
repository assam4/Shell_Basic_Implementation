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
	{
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
	}
}
