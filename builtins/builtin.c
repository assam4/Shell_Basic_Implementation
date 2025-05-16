/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:46:27 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/16 20:45:43 by aadyan           ###   ########.fr       */
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

bool	exec_builtin(t_list *cmd)
{
	char	*word;

	if (!cmd || !cmd->content)
		return (false);
	word = ((t_token *)cmd->content)->word;
	if (ft_strncmp(word, "echo", ft_strlen(word) + 1) == 0)
		return (echo(cmd));
	if (ft_strncmp(word, "unset", ft_strlen(word) + 1) == 0)
		return (true);
	if (ft_strncmp(word, "export", ft_strlen(word) + 1) == 0)
		return (true);
	if (ft_strncmp(word, "exit", ft_strlen(word) + 1) == 0)
		return (true);
	if (ft_strncmp(word, "env", ft_strlen(word) + 1) == 0)
		return (true);
	if (ft_strncmp(word, "cd", ft_strlen(word) + 1) == 0)
		return (cd(cmd));
	if (ft_strncmp(word, "pwd", ft_strlen(word) + 1) == 0)
		return (pwd(cmd));
	return (false);
}
