/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:16:09 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/19 21:40:17 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

bool	export(t_list *cmd, t_env *var)
{
	char	*eval;

	cmd = cmd->next;
	while (cmd)
	{
		eval = ft_strchr(((t_token *)cmd->content)->word, '=');
		if (((t_token *)cmd->content)->word == eval)
			return (ft_putstr_fd("minishell: export: ", 2),
				ft_putstr_fd(((t_token *)cmd->content)->word, 2),
				ft_putstr_fd(": not a valid identifier\n", 2), false);
		add_var(var, ((t_token *)cmd->content)->word);
		cmd = cmd->next;
	}
	return (true);
}
