/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:00:31 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/16 20:41:37 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

bool	pwd(t_list *cmd)
{
	char	*cwd;

	if (cmd->next)
	{
		ft_putstr_fd("minishell: pwd: too many arguments\n", 2);
		return (false);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror("minishell"), false);
	ft_putstr_fd(cwd, 1);
	ft_putchar_fd('\n', 1);
	free(cwd);
	return (true);
}
