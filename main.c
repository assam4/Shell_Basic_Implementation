/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:47:20 by saslanya          #+#    #+#             */
/*   Updated: 2025/05/21 01:32:24 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	g_exit_status = EXIT_SUCCESS;

static int	run_shell(t_list **tokens, t_env *vars)
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
		execute_node(tree, vars);
	tree_felling(&tree);
	return (EXIT_SUCCESS);
}

static char	*get_prompt_line(t_env *vars)
{
	char	*user;
	char	*pwd;
	char	*prompt;
	int		total_len;

	user = get_env_value("USER=", vars->env);
	pwd = getcwd(NULL, 0);
	if (!user)
		user = ft_strdup("unknown");
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

static int	exec_line(t_env *vars)
{
	char	*line;
	t_list	*tokens;
	char	*prompt;

	while (1)
	{
		prompt = get_prompt_line(vars);
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
		run_shell(&tokens, vars);
		free(prompt);
	}
	return (free(line), free(prompt), EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*vars;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd(strerror(EINVAL), STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		return (EINVAL);
	}
	vars = get_env(envp);
	if (!vars)
		return (ENOMEM);
	exec_line(vars);
	destroy_env(&vars);
	return (EXIT_SUCCESS);
}
