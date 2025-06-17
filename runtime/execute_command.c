/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:31:22 by aadyan            #+#    #+#             */
/*   Updated: 2025/06/17 19:26:16 by aadyan           ###   ########.fr       */
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
		replace_chars(splited_cmd[i], 2, ' ');
		++i;
	}
	execve(cmd, splited_cmd, env);
	free(cmd);
	cmd = get_env_value("PATH=", env);
	if (errno == EFAULT && !cmd && splited_cmd)
		print_error(splited_cmd[0], ": no such file or directory\n", false);
	else if (errno == EFAULT && splited_cmd)
		print_error(splited_cmd[0], ": command not found\n", false);
	else
		perror("minishell");
	free(cmd);
	ft_split_free(splited_cmd);
	exit(errno);
}

static int	create_fork(t_ast_node *node, t_env *vars, int s, char *cmd)
{
	char			**splited_cmd;
	pid_t			pid;
	struct termios	oldt;

	if (!init_cmds(&cmd, &splited_cmd, node, vars) || !set_redirs(node))
		return (free(cmd), ft_split_free(splited_cmd), 0);
	s = is_builtin(node->cmd);
	if (s)
		return (free(cmd), ft_split_free(splited_cmd),
			exec_builtin(node->cmd, vars));
	tcgetattr(STDIN_FILENO, &oldt);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		execution(cmd, splited_cmd, vars->env);
	}
	signal(SIGINT, handler);
	waitpid(pid, &s, 0);
	if (WTERMSIG(s) == SIGQUIT)
		ft_putstr_fd(CORE_DUMPED, STDERR_FILENO);
	return (tcsetattr(STDIN_FILENO, TCSANOW, &oldt), ft_split_free(splited_cmd),
		free(cmd), set_exit_status(vars, s), WIFEXITED(s) && !(WEXITSTATUS(s)));
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
	status = create_fork(node, vars, EXIT_SUCCESS, NULL);
	dup2(stdin_cpy, STDIN_FILENO);
	dup2(stdout_cpy, STDOUT_FILENO);
	close(stdin_cpy);
	close(stdout_cpy);
	return (status);
}
