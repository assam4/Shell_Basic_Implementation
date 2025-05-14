/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 01:08:23 by saslanya          #+#    #+#             */
/*   Updated: 2025/05/14 17:20:09 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	run_shell(t_list **tokens, char **envp)
{
	t_ast_node	*tree;

	tree = NULL;
	if (!syntax_analyse(*tokens))
		return (ft_lstclear(tokens, token_free), EX_USAGE);
	tree = ft_calloc(1, sizeof(t_ast_node));
	if (!tree)
		return (ft_putstr_fd("Allocation error\n", STDERR_FILENO), ENOMEM);
	if (tree_blossom(tree, *tokens))
		execute_node(tree, envp);
	tree_felling(&tree);
	return (EXIT_SUCCESS);
}

static char	*fd_getline(void)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("minishel> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			line = get_next_line(STDIN_FILENO);
		else if (line && !ft_strncmp(line, "exit\n", 5))
			break ;
		else if (*line == NEWLINE)
		{
			free(line);
			continue ;
		}
		else
			return (line);
	}
	free(line);
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_list	*tokens;

	(void)argv;
	if (argc != 1)
		return (ft_putstr_fd("WRONG ARGS", STDERR_FILENO), EXIT_FAILURE);
	while (1)
	{
		tokens = NULL;
		line = fd_getline();
		if (!line)
			break ;
		if (!get_tokens(line, &tokens))
			return (free(line)
				, ft_putstr_fd("Tokenization error\n", STDERR_FILENO), ENOMEM);
		free(line);
		run_shell(&tokens, envp);
	}
	return (EXIT_SUCCESS);
}
