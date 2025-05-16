/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:24:44 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/16 16:04:10 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

bool	echo(t_list *cmd)
{
	int		new_line;

	new_line = 1;
	cmd = cmd->next;
	if (ft_strncmp(((t_token *)cmd->content)->word, "-n",
			ft_strlen(((t_token *)cmd->content)->word + 1)) == 0)
	{
		new_line = 0;
		cmd = cmd->next;
	}
	while (cmd)
	{
		if (!((t_token *)cmd->content)->word)
			return (false);
		ft_putstr_fd(((t_token *)cmd->content)->word, 1);
		if (cmd->next)
			ft_putchar_fd(' ', 1);
		cmd = cmd->next;
	}
	if (new_line)
		ft_putchar_fd('\n', 1);
	return (true);
}
