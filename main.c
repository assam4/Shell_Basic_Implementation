/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:47:20 by saslanya          #+#    #+#             */
/*   Updated: 2025/05/16 10:19:04 by saslanya         ###   ########.fr       */
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
	{
		ft_putstr_fd(strerror(ENOMEM), STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		return (ENOMEM);
	}
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
	prompt = ft_calloc(total_len, sizeof(char));
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

	while (1)
	{
		prompt = get_prompt_line(envp);
		tokens = NULL;
		line = readline(prompt);
		if (line && *line)
			add_history(line);
		if (!line || !strncmp(line, EXIT, ft_strlen(line)))
			break ;
		if (!get_tokens(line, &tokens))
			return (free(line), free(prompt),
				ft_putstr_fd(strerror(ENOMEM), STDERR_FILENO),
				ft_putchar_fd('\n', STDERR_FILENO), ENOMEM);
		if (!tokens)
			continue ;
		free(line);
		run_shell(&tokens, envp);
		free(prompt);
	}
	return (free(line), free(prompt), EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd(strerror(EINVAL), STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		return (EINVAL);
	}
	exec_line(envp);
	return (EXIT_SUCCESS);
}
