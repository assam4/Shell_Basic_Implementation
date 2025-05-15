/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 01:08:23 by saslanya          #+#    #+#             */
/*   Updated: 2025/05/15 21:27:57 by aadyan           ###   ########.fr       */
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

static char	*get_prompt_line(char **env)
{
	char	*user;
	char	*pwd;
	char	*prompt;
	int		total_len;

	user = get_env_value(env, "USER=");
	pwd = get_env_value(env, "PWD=");
	if (!user)
		user = "unknown";
	total_len = ft_strlen(GREEN) + ft_strlen(user) + ft_strlen(BLUE)
		+ ft_strlen(pwd) + ft_strlen(RESET) + 13;
	prompt = malloc(total_len);
	if (!prompt)
		return (NULL);
	ft_strlcpy(prompt, GREEN, total_len);
	ft_strlcat(prompt, "minishell@", total_len);
	ft_strlcat(prompt, user, total_len);
	ft_strlcat(prompt, ":", total_len);
	ft_strlcat(prompt, BLUE, total_len);
	ft_strlcat(prompt, pwd, total_len);
	ft_strlcat(prompt, "$ ", total_len);
	ft_strlcat(prompt, RESET, total_len);
	free(user);
	free(pwd);
	return (prompt);
}

static int	exec_line(char **envp)
{
	char	*line;
	t_list	*tokens;
	char	*prompt;

	prompt = get_prompt_line(envp);
	while (1)
	{
		tokens = NULL;
		line = readline(prompt);
		if (line && *line)
			add_history(line);
		if (!line)
			break ;
		if (!get_tokens(line, &tokens))
			return (free(line), free(prompt),
				ft_putstr_fd("Tokenization error\n", STDERR_FILENO), ENOMEM);
		if (!tokens)
			continue ;
		free(line);
		run_shell(&tokens, envp);
	}
	free(prompt);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 1)
		return (ft_putstr_fd("WRONG ARGS", STDERR_FILENO), EXIT_FAILURE);
	exec_line(envp);
	return (EXIT_SUCCESS);
}
