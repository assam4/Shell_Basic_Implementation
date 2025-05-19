/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:54:04 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/19 20:58:56 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

bool	unset(t_list *cmd, t_env *var)
{
	cmd = cmd->next;
	while (cmd)
	{
		del_var(var, ((t_token *)cmd->content)->word);
		cmd = cmd->next;
	}
	return (true);
}
