/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:46:05 by saslanya          #+#    #+#             */
/*   Updated: 2025/05/23 16:33:42 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool	complete_command(t_list *tokens)
{
	t_token		*current;
	t_token		*last;
	int			count;

	last = NULL;
	count = 0;
	while (tokens)
	{
		current = (t_token *)tokens->content;
		if (current->o_type == OP_SUBSHELL_OPEN)
			++count;
		if (current->o_type == OP_SUBSHELL_CLOSE)
			--count;
		last = current;
		tokens = tokens->next;
	}
	if (count != 0)
		return (false);
	if (!last)
		return (true);
	if (last->o_type == OP_AND || last->o_type == OP_OR
		|| last->o_type == OP_PIPE)
		return (false);
	return (true);
}

static int	run_shell(t_list **tokens, t_env *vars)
{
	t_ast_node	*tree;

	if (!syntax_analyse(*tokens))
		return (ft_lstclear(tokens, token_free), EXIT_FAILURE);
	while (!complete_command(*tokens))
	{
		if (!command_loop(tokens, vars))
			return (ft_lstclear(tokens, token_free), EXIT_FAILURE);
		if (!syntax_analyse(*tokens))
			return (ft_lstclear(tokens, token_free), EXIT_FAILURE);
		if (g_signal)
			return (ft_lstclear(tokens, token_free), EXIT_FAILURE);
	}
	tree = ft_calloc(1, sizeof(t_ast_node));
	if (!tree)
		return (ft_lstclear(tokens, token_free), EXIT_FAILURE);
	if (*tokens && tree_blossom(tree, *tokens))
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

static int	execute_line(t_env *vars)
{
	char	*line;
	t_list	*tokens;
	char	*prompt;

	while (g_signal != -1)
	{
		g_signal = 0;
		prompt = get_prompt_line(vars);
		if (!prompt)
			return (print_err(ENOMEM));
		tokens = NULL;
		line = readline(prompt);
		if (line && *line && *line != '\n')
			add_history(line);
		if (!line)
			return (ft_putstr_fd(EXIT, STDOUT_FILENO)
				, free(prompt), vars->exit_status);
		++(vars->line_count);
		if (!get_tokens(line, &tokens))
			return (free(line), free(prompt), print_err(ENOMEM));
		free(line);
		run_shell(&tokens, vars);
		free(prompt);
	}
	return (vars->exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*vars;
	int		exit_status;

	(void)argv;
	if (argc != 1)
		return (print_err(EINVAL));
	vars = get_env(envp);
	if (!vars)
		return (print_err(ENOMEM));
	sig_config();
	exit_status = execute_line(vars);
	destroy_env(&vars);
	return (exit_status);
}
