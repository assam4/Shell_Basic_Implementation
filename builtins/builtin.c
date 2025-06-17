/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:46:27 by aadyan            #+#    #+#             */
/*   Updated: 2025/06/17 16:33:24 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

bool	is_builtin(t_list *cmd)
{
	char	*word;

	if (!cmd || !cmd->content)
		return (false);
	word = ((t_token *)cmd->content)->word;
	if (ft_strncmp(word, "echo", ft_strlen(word) + 1) == 0)
		return (true);
	if (ft_strncmp(word, "unset", ft_strlen(word) + 1) == 0)
		return (true);
	if (ft_strncmp(word, "export", ft_strlen(word) + 1) == 0)
		return (true);
	if (ft_strncmp(word, "exit", ft_strlen(word) + 1) == 0)
		return (true);
	if (ft_strncmp(word, "env", ft_strlen(word) + 1) == 0)
		return (true);
	if (ft_strncmp(word, "cd", ft_strlen(word) + 1) == 0)
		return (true);
	if (ft_strncmp(word, "pwd", ft_strlen(word) + 1) == 0)
		return (true);
	return (false);
}

bool	exec_builtin(t_list *cmd, t_env *var)
{
	char	*word;

	if (!cmd || !cmd->content)
		return (var->exit_status = 1, false);
	word = ((t_token *)cmd->content)->word;
	if (ft_strncmp(word, "echo", ft_strlen(word) + 1) == 0)
		var->exit_status = !echo(cmd);
	else if (ft_strncmp(word, "unset", ft_strlen(word) + 1) == 0)
		var->exit_status = !unset(cmd, var);
	else if (ft_strncmp(word, "export", ft_strlen(word) + 1) == 0)
		var->exit_status = !export(cmd, var);
	else if (ft_strncmp(word, "exit", ft_strlen(word) + 1) == 0)
		builtin_exit(cmd, var);
	else if (ft_strncmp(word, "env", ft_strlen(word) + 1) == 0)
		env(cmd, var);
	else if (ft_strncmp(word, "cd", ft_strlen(word) + 1) == 0)
		var->exit_status = !cd(cmd, var);
	else if (ft_strncmp(word, "pwd", ft_strlen(word) + 1) == 0)
		var->exit_status = !pwd(cmd, var);
	return (!var->exit_status);
}
