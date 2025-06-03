/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:24:44 by aadyan            #+#    #+#             */
/*   Updated: 2025/06/03 15:32:26 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	check_flag(t_list **cmd, int *new_line)
{
	int	i;

	while (ft_strncmp(((t_token *)(*cmd)->content)->word, "-n", 2) == 0)
	{
		i = 1;
		while (((t_token *)(*cmd)->content)->word[i] &&
				((t_token *)(*cmd)->content)->word[i] == 'n')
			i++;
		if (!((t_token *)(*cmd)->content)->word[i])
		{
			*new_line = 0;
			(*cmd) = (*cmd)->next;
		}
	}
}

bool	echo(t_list *cmd)
{
	int	new_line;

	new_line = 1;
	cmd = cmd->next;
	if (!cmd)
		return (ft_putchar_fd('\n', 1), true);
	check_flag(&cmd, &new_line);
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
