/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:11:57 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/24 19:16:58 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	update_oldpwd(t_env *var, char *oldpwd)
{
	char	*full_pwd;

	full_pwd = ft_strjoin("OLDPWD=", oldpwd);
	free(oldpwd);
	if (!full_pwd)
		return (false);
	if (!add_var(var, full_pwd))
		return (false);
	return (true);
}

static bool	update_pwd(t_env *var)
{
	char	*pwd;
	char	*full_pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (false);
	full_pwd = ft_strjoin("PWD=", pwd);
	free(pwd);
	if (!full_pwd)
		return (false);
	if (!add_var(var, full_pwd))
		return (false);
	return (true);
}

bool	cd(t_list *cmd, t_env *var)
{
	char	*tmp;

	if (!cmd->next)
		return (true);
	if (cmd->next->next)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (false);
	}
	tmp = get_env_value("PWD=", var->env);
	if (!tmp)
		return (false);
	if (chdir(((t_token *)cmd->next->content)->word) == -1)
		return (print_error("cd: ", NULL, 1), false);
	if (!update_oldpwd(var, tmp))
		return (print_error("cd: ", NULL, 1), false);
	if (!update_pwd(var))
		return (print_error("cd: ", NULL, 1), false);
	return (true);
}
