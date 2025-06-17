/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:15:02 by aadyan            #+#    #+#             */
/*   Updated: 2025/06/17 16:33:26 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

bool	env(t_list *cmd, t_env *var)
{
	char	*tmp;

	tmp = get_env_value("PATH=", var->env);
	if (!tmp)
		return (print_error("env: ", "no such file or directory\n",
				false), var->exit_status = 127, false);
	if (cmd->next)
	{
		free(tmp);
		ft_putstr_fd(((t_token *)cmd->content)->word, STDERR_FILENO);
		ft_putstr_fd(": ‘", STDERR_FILENO);
		ft_putstr_fd(((t_token *)cmd->next->content)->word, STDERR_FILENO);
		ft_putstr_fd("’: No such file or directory\n", STDERR_FILENO);
		var->exit_status = 127;
		return (false);
	}
	print_env(var);
	return (free(tmp), var->exit_status = 0, true);
}
