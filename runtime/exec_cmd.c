/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:31:22 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/14 02:36:21 by aadyan           ###   ########.fr       */
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

bool	execute_cmd(t_ast_node *node, char **env)
{
	pid_t	pid;
	char	**splited_cmd;
	char	*cmd;
	int		status;

	if (!set_redirs(node))
		return (false);
	else if (!node->cmd)
		return (true);
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
