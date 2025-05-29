/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:11:57 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/29 16:11:15 by aadyan           ###   ########.fr       */
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

static bool	update_pwd(t_env *var, char *dir)
{
	char	*pwd;
	char	*full_pwd;
	char	*env_val;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		pwd = get_env_value("PWD=", var->env);
		full_pwd = ft_join_with_sep(pwd, dir, '/');
		env_val = ft_strjoin("PWD=", full_pwd);
		free(full_pwd);
		if (!add_var(var, env_val))
			return (false);
		return (free(pwd),
			print_error("cd: error retrieving current directory: ", NULL, 0),
			ft_putstr_fd("getcwd: cannot access parent directories: ", 2),
			ft_putstr_fd("No such file or directory\n", 2), true);
	}
	full_pwd = ft_strjoin("PWD=", pwd);
	free(pwd);
	if (!full_pwd)
		return (false);
	if (!add_var(var, full_pwd))
		return (false);
	return (true);
}

static bool cd_home(t_env *var)
{
	char	*tmp;

	tmp = get_env_value("HOME=", var->env);
	if (!tmp)
		return (print_error("cd: ", "HOME not set", false), false);
	if (chdir(tmp) == -1)
		return (print_error("cd: ", NULL, 1), free(tmp), false);
	if (!update_oldpwd(var, tmp))
		return (print_error("cd: ", NULL, 1), false);
	if (update_pwd(var, tmp) == 0)
		return (print_error("cd: ", NULL, 1), false);
	return (true);
}

bool	cd(t_list *cmd, t_env *var)
{
	char	*tmp;

	if (!cmd->next)
		return (cd_home(var));
	if (cmd->next->next)
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2),
			false);
	tmp = get_env_value("PWD=", var->env);
	if (!tmp)
		return (false);
	if (chdir(((t_token *)cmd->next->content)->word) == -1)
		return (print_error("cd: ", NULL, 1), false);
	if (!update_oldpwd(var, tmp))
		return (print_error("cd: ", NULL, 1), false);
	if (update_pwd(var, ((t_token *)cmd->next->content)->word) == 0)
		return (print_error("cd: ", NULL, 1), false);
	return (true);
}
