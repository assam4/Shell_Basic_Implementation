/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:45:27 by saslanya          #+#    #+#             */
/*   Updated: 2025/05/19 21:06:34 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	print_error(char *mess1, char *mess2, bool flag)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(mess1, STDERR_FILENO);
	if (mess2)
		ft_putstr_fd(mess2, STDERR_FILENO);
	if (flag)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		perror("");
	}
}

static bool	execute_subshell(t_ast_node *node, t_env *vars)
{
	pid_t	process_id;
	int		status;

	process_id = fork();
	if (!process_id)
	{
		if (execute_node(node->left, vars))
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

static bool	stream_change(pid_t *process_id, t_ast_node *left,
			t_ast_node *right, t_env *vars)
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
		exit(!execute_node(left, vars));
	}
	process_id[1] = fork();
	if (process_id[1] == -1)
		return (close(fd[0]), close(fd[1]), false);
	if (!process_id[1])
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		exit(!execute_node(right, vars));
	}
	return (close(fd[0]), close(fd[1]), true);
}

static bool	execute_pipe(t_ast_node *left, t_ast_node *right, t_env *vars)
{
	pid_t	process_id[2];
	int		status[2];
	int		stdout_cpy;

	stdout_cpy = dup(STDOUT_FILENO);
	if (!stream_change(process_id, left, right, vars))
		return (false);
	waitpid(process_id[0], status, 0);
	waitpid(process_id[1], status + 1, 0);
	dup2(STDOUT_FILENO, stdout_cpy);
	close(stdout_cpy);
	return ((WIFEXITED(status[0]) && !WEXITSTATUS(status[0]))
		&& (WIFEXITED(status[1]) && !WEXITSTATUS(status[1])));
}

bool	execute_node(t_ast_node *node, t_env *vars)
{
	if (!node)
		return (true);
	else if (node->token->o_type == OP_AND)
		return (execute_node(node->left, vars)
			&& execute_node(node->right, vars));
	else if (node->token->o_type == OP_OR)
		return (execute_node(node->left, vars)
			|| execute_node(node->right, vars));
	else if (node->token->o_type == OP_PIPE)
		return (execute_pipe(node->left, node->right, vars));
	else if (node->token->o_type == OP_SUBSHELL_OPEN)
		return (execute_subshell(node, vars));
	else
		return (execute_cmd(node, vars));
}
