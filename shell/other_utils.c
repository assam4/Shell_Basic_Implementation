/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:29:37 by aadyan            #+#    #+#             */
/*   Updated: 2025/06/11 20:13:04 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	set_exit_status(t_env *vars, int status)
{
	if (WIFSIGNALED(status))
		vars->exit_status = 128 + WTERMSIG(status);
	else if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == EACCES)
			vars->exit_status = 126;
		else if (WEXITSTATUS(status) == ENOENT)
			vars->exit_status = 127;
		else
			vars->exit_status = WEXITSTATUS(status);
	}
}

void	content_swap(t_list *first, t_list *second)
{
	void	*tmp;

	tmp = first->content;
	first->content = second->content;
	second->content = tmp;
}
