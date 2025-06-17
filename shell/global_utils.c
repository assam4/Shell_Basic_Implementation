/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:29:37 by aadyan            #+#    #+#             */
/*   Updated: 2025/06/18 00:51:47 by saslanya         ###   ########.fr       */
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
		else if (WEXITSTATUS(status) == EFAULT)
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

bool	update_shlvl(char **s)
{
	char	*lvl_str;
	int		lvl;

	lvl = ft_atoi(*s + LEN) + 1;
	lvl_str = ft_itoa(ft_atoi(*s + LEN) + 1);
	if (!lvl_str)
		return (false);
	if (lvl >= MAX_LVL)
	{
		ft_putstr_fd("minishell: warning: shell level (", STDERR_FILENO);
		ft_putstr_fd(lvl_str, STDERR_FILENO);
		ft_putstr_fd(") too high, resetting to 1\n", STDERR_FILENO);
		return (free(lvl_str), false);
	}
	free(*s);
	*s = ft_calloc(LEN + ft_strlen(lvl_str) + 1, sizeof(char));
	if (!*s)
		return (free(lvl_str), false);
	ft_strlcpy(*s, SHLVL, LEN + 1);
	ft_strlcpy(*s + LEN, lvl_str, ft_strlen(lvl_str) + 1);
	return (free(lvl_str), true);
}

void	check_secret_pwd(char **secret_pwd)
{
	char	*pwd;
	char	*full_pwd;

	if (!*secret_pwd)
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			pwd = ft_strdup(".");
		full_pwd = ft_strjoin("PWD=", pwd);
		*secret_pwd = full_pwd;
		free(pwd);
	}
}
