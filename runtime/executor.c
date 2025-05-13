/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:39:03 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/13 20:40:57 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static bool	execute_subshell(t_ast_node *node, char **env)
{
	pid_t	process_id;
	int		status;

	process_id = fork();
	if (!process_id)
	{
		if (execute_node(node->left, env))
			exit(EXIT_SUCCESS);
		else
			exit(EXIT_FAILURE);
	}
	else if (process_id > 0)
	{
		waitpid(process_id, &status, 0);
		return (WIFEXITED(status) && !(WEXITSTATUS(status)));
	}
	else
		return (false);
}

bool	execute_node(t_ast_node *node, char **env)
{
	if (!node)
		return (true);
	else if (node->token->o_type == OP_AND)
		return (execute_node(node->left, env)
			&& execute_node(node->right, env));
	else if (node->token->o_type == OP_OR)
		return (execute_node(node->left, env)
			|| execute_node(node->right, env));
	else if (node->token->o_type == OP_SUBSHELL_OPEN)
		return (execute_subshell(node, env));
	else
		return (execute_cmd(node, env));
}
