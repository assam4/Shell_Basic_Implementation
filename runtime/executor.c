/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 21:32:03 by saslanya          #+#    #+#             */
/*   Updated: 2025/05/13 21:54:02 by saslanya         ###   ########.fr       */
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

static bool	stream_change(pid_t *process_id, t_ast_node *left
			, t_ast_node *right, char **env)
{
	int	fd[2];

	if (pipe(fd) < 0)
		return (false);
	process_id[0] = fork();
	if (process_id[0] == -1)
		return (close(fd[0]), close(fd[1]), false);
	if (!process_id[0])
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		exit(!execute_node(left, env));
	}
	process_id[1] = fork();
	if (process_id[1] == -1)
		return (close(fd[0]), close(fd[1]), false);
	if (!process_id[1])
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		exit(!execute_node(right, env));
	}
	return (close(fd[0]), close(fd[1]), true);
}

static bool	execute_pipe(t_ast_node *left, t_ast_node *right, char **env)
{
	pid_t	process_id[2];
	int		status[2];

	if (!stream_change(process_id, left, right, env))
		return (false);
	waitpid(process_id[0], status, 0);
	waitpid(process_id[1], status + 1, 0);
	return ((WIFEXITED(status[0]) && !WEXITSTATUS(status[0]))
		&& (WIFEXITED(status[1]) && !WEXITSTATUS(status[1])));
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
	else if (node->token->o_type == OP_PIPE)
		return (execute_pipe(node->left, node->right, env));
	else if (node->token->o_type == OP_SUBSHELL_OPEN)
		return (execute_subshell(node, env));
	else
		return (execute_cmd(node, env));
}
