/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:15:02 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/29 16:35:30 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

bool	env(t_list *cmd, t_env *var)
{
	char	*tmp;

	tmp = get_env_value("PATH=", var->env);
	if (!tmp)
		return (print_error("env: ", "no such file or directory\n", false), false);
	if (cmd->next)
		return (free(tmp), print_error("env", "too many arguments", 0), 1);
	print_env(var);
	return (free(tmp), 0);
}
