/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:31:22 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/19 00:36:46 by saslanya         ###   ########.fr       */
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

static int	create_fork(t_ast_node *node, t_env *vars, int status)
{
	char	*cmd;
	char	**splited_cmd;
	pid_t	pid;

	if (!init_cmds(&cmd, &splited_cmd, node, vars->env))
		return (0);
	status = is_builtin(node->cmd);
	if (status)
		return (free(cmd), ft_split_free(splited_cmd), exec_builtin(node->cmd));
	pid = fork();
	if (pid == 0)
	{
		execve(cmd, splited_cmd, vars->env);
		free(cmd);
		cmd = get_env_value("PATH:", vars->env);
		if (!cmd)
			print_error(splited_cmd[0], ": no such file or directory\n", false);
		else if (splited_cmd)
			print_error(splited_cmd[0], ": command not found\n", false);
		free(cmd);
		ft_split_free(splited_cmd);
		exit(EXIT_FAILURE);
	}
	return (free(cmd), ft_split_free(splited_cmd), waitpid(pid, &status, 0)
		, WIFEXITED(status) && !(WEXITSTATUS(status)));
}

bool	execute_cmd(t_ast_node *node, t_env *vars)
{
	int		status;
	int		stdin_cpy;
	int		stdout_cpy;

	stdin_cpy = dup(STDIN_FILENO);
	stdout_cpy = dup(STDOUT_FILENO);
	if (node->token->t_type == WORD && node->cmd
		&& ((t_token *)node->cmd->content)->is_tmp)
		return (true);
	if (!set_redirs(node))
		return (false);
	status = create_fork(node, vars, EXIT_SUCCESS);
	dup2(stdin_cpy, STDIN_FILENO);
	dup2(stdout_cpy, STDOUT_FILENO);
	close(stdin_cpy);
	close(stdout_cpy);
	return (status);
}
