/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:31:22 by aadyan            #+#    #+#             */
/*   Updated: 2025/06/03 14:30:36 by aadyan           ###   ########.fr       */
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
		t_ast_node *node, t_env *var)
{
	char	*full_cmd;

	full_cmd = get_cmd(node->cmd, var);
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
	*cmd = ret_command((*splited_cmd)[0], var->env);
	return (true);
}

static void	execution(char *cmd, char **splited_cmd, char **env)
{
	int	i;

	if (!splited_cmd)
		exit(EXIT_FAILURE);
	i = 0;
	while (splited_cmd[i])
	{
		replace_chars(splited_cmd[i], 1, ' ');
		++i;
	}
	execve(cmd, splited_cmd, env);
	free(cmd);
	cmd = get_env_value("PATH=", env);
	if (errno == 14 && !cmd && splited_cmd)
		print_error(splited_cmd[0], ": no such file or directory\n", false);
	else if (errno == 14 && splited_cmd)
		print_error(splited_cmd[0], ": command not found\n", false);
	else
		perror("minishell");
	free(cmd);
	ft_split_free(splited_cmd);
	exit(EXIT_FAILURE);
}

static int	create_fork(t_ast_node *node, t_env *vars, int status)
{
	char			*cmd;
	char			**splited_cmd;
	pid_t			pid;
	struct termios	oldt;

	if (!init_cmds(&cmd, &splited_cmd, node, vars))
		return (0);
	status = is_builtin(node->cmd);
	if (status)
		return (free(cmd), ft_split_free(splited_cmd),
			exec_builtin(node->cmd, vars));
	tcgetattr(STDIN_FILENO, &oldt);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		execution(cmd, splited_cmd, vars->env);
	}
	return (free(cmd), ft_split_free(splited_cmd), waitpid(pid, &status, 0),
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt),
		WIFEXITED(status) && !(WEXITSTATUS(status)));
}

bool	execute_cmd(t_ast_node *node, t_env *vars)
{
	int		status;
	int		stdin_cpy;
	int		stdout_cpy;

	if (g_signal)
		return (false);
	stdin_cpy = dup(STDIN_FILENO);
	if (stdin_cpy < 0)
		return (false);
	stdout_cpy = dup(STDOUT_FILENO);
	if (stdout_cpy < 0)
		return (close(stdin_cpy), false);
	if (!node || !node->cmd)
		return (close(stdin_cpy), close(stdout_cpy), true);
	if (node->token->t_type == WORD && node->cmd
		&& ((t_token *)node->cmd->content)->is_tmp)
		return (close(stdin_cpy), close(stdout_cpy), true);
	if (!set_redirs(node))
		return (close(stdin_cpy), close(stdout_cpy), false);
	status = create_fork(node, vars, EXIT_SUCCESS);
	dup2(stdin_cpy, STDIN_FILENO);
	dup2(stdout_cpy, STDOUT_FILENO);
	close(stdin_cpy);
	close(stdout_cpy);
	return (vars->exit_status = status, status);
}
