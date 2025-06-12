/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:00:31 by aadyan            #+#    #+#             */
/*   Updated: 2025/06/13 01:17:55 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

bool	pwd(t_list *cmd, t_env *var)
{
	if (cmd->next)
	{
		ft_putstr_fd("minishell: pwd: too many arguments\n",
			STDERR_FILENO);
		return (false);
	}
	ft_putstr_fd(var->secret_pwd + 4, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (true);
}
