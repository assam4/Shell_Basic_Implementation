/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:15:02 by aadyan            #+#    #+#             */
/*   Updated: 2025/06/17 17:34:14 by saslanya         ###   ########.fr       */
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
		print_error("env: too many arguments\n", NULL, false);
		return (free(tmp), var->exit_status = 1, false);
	}
	print_env(var);
	return (free(tmp), var->exit_status = 0, true);
}
