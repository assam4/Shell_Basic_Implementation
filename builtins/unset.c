/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:54:04 by aadyan            #+#    #+#             */
/*   Updated: 2025/06/12 17:43:25 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

bool	unset(t_list *cmd, t_env *var)
{
	if (cmd->next
		&& ft_strncmp(((t_token *)cmd->next->content)->word, "_", 2) == 0)
		return (true);
	cmd = cmd->next;
	while (cmd)
	{
		del_var(var, ((t_token *)cmd->content)->word);
		cmd = cmd->next;
	}
	return (true);
}
