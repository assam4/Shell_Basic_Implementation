/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:29:37 by aadyan            #+#    #+#             */
/*   Updated: 2025/06/04 21:17:34 by aadyan           ###   ########.fr       */
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
