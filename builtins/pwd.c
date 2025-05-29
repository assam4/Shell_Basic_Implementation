/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:00:31 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/29 22:42:39 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

bool	pwd(t_list *cmd, t_env *var)
{
	if (cmd->next)
	{
		ft_putstr_fd("minishell: pwd: too many arguments\n", 2);
		return (false);
	}
	ft_putstr_fd(var->secret_pwd, 1);
	ft_putchar_fd('\n', 1);
	return (true);
}
