/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:31:22 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/14 18:03:51 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	ft_split_free(char **arr)
{
	int	i;

	i = -1;
	if (!arr)
		return ;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

static bool	init_cmds(char **cmd, char ***splited_cmd,
		t_ast_node *node, char **env)
{
	char	*full_cmd;

	full_cmd = get_cmd(node->cmd);
	if (!full_cmd)
		return (false);
	if (!*full_cmd)
	{
		*splited_cmd = NULL;
		return (free(full_cmd), true);
	}
	*splited_cmd = ft_split(full_cmd, ' ');
	free(full_cmd);
	if (!*splited_cmd)
		return (false);
	*cmd = ret_command((*splited_cmd)[0], env);
	return (true);
}

static void	print_error(char *cmd, char *mess)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(mess, STDERR_FILENO);
}

static int	create_fork(t_ast_node *node, char **env)
{
	char	*cmd;
	char	**splited_cmd;
	int		status;
	pid_t	pid;

	if (!init_cmds(&cmd, &splited_cmd, node, env))
		return (false);
	pid = fork();
	if (pid == 0)
	{
		execve(cmd, splited_cmd, env);
		if (splited_cmd)
			print_error(splited_cmd[0], ": command not found\n");
		free(cmd);
		ft_split_free(splited_cmd);
		exit(EXIT_FAILURE);
	}
	free(cmd);
	ft_split_free(splited_cmd);
	waitpid(pid, &status, 0);
	return (WIFEXITED(status) && !(WEXITSTATUS(status)));
}

bool	execute_cmd(t_ast_node *node, char **env)
{
	int		status;
	int		stdin_cpy;
	int		stdout_cpy;

	stdin_cpy = dup(STDIN_FILENO);
	stdout_cpy = dup(STDOUT_FILENO);
	if (!node->cmd)
		return (true);
	if (node->token->t_type == WORD
		&& ((t_token *)node->cmd->content)->is_tmp)
		return (true);
	if (!set_redirs(node))
		return (false);
	status = create_fork(node, env);
	dup2(stdin_cpy, STDIN_FILENO);
	dup2(stdout_cpy, STDOUT_FILENO);
	close(stdin_cpy);
	close(stdout_cpy);
	return (status);
}
