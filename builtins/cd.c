/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:11:57 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/16 20:54:24 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

bool	cd(t_list *cmd)
{
	if (!cmd->next)
		return (true);
	if (cmd->next->next)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (false);
	}
	if (chdir(((t_token *)cmd->next->content)->word) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(((t_token *)cmd->next->content)->word);
		return (false);
	}
	return (true);
}
