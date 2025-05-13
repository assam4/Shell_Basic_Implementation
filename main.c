/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 01:08:23 by saslanya          #+#    #+#             */
/*   Updated: 2025/05/14 01:08:23 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	run_shell(t_list **tokens, char **envp)
{
	t_ast_node	*tree;

	tree = NULL;
	if (!syntax_analyse(*tokens))
			return (ft_putstr_fd("❌ Syntax error\n", STDERR_FILENO)
				,ft_lstclear(tokens, token_free), EX_USAGE);
	tree = ft_calloc(1, sizeof(t_ast_node));
		if (!tree)
			return (ft_putstr_fd("Allocation error\n", STDERR_FILENO), ENOMEM);
		if (tree_blossom(tree, *tokens))
			execute_node(tree, envp);
		tree_felling(&tree);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	int		status;
	t_list	*tokens;

	(void)argv;
	if (argc != 1)
		return (ft_putstr_fd("INCORRECT ARGS count!.", STDERR_FILENO), EXIT_FAILURE);
	while (1)
	{
		tokens = NULL;
		ft_putstr_fd("minishel: ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line || !ft_strncmp(line, "exit\n", 5))
		{
			free(line);
			break ;
		}
		if (!get_tokens(line, &tokens))
		return (free(line), ft_putstr_fd("❌ Tokenization error\n", STDERR_FILENO), ENOMEM);
		free(line);
		status = run_shell(&tokens, envp);
		if (status)
			return (status);
	}
	return (EXIT_SUCCESS);
}
