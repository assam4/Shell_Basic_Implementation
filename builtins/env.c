/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:15:02 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/19 19:52:24 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

bool	env(t_list *cmd, t_env *var)
{
	if (cmd->next)
		return (print_error("env", "too many arguments", 0), 1);
	print_env(var);
	return (0);
}
