/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:37:52 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/29 22:45:09 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

bool	env_value_exists(char *key, t_env *var)
{
	size_t	key_len;
	int		i;

	i = -1;
	key_len = ft_strlen(key);
	while (var->env[++i])
		if (ft_strncmp(var->env[i], key, key_len) == 0)
			return (true);
	return (false);
}

bool	update_oldpwd(t_env *var, char *oldpwd)
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

bool	update_pwd_helper(t_env *var, char *dir)
{
	char	*full_pwd;

	full_pwd = ft_join_with_sep(var->secret_pwd, dir, '/');
	if (env_value_exists("PWD=", var))
	{
		if (!add_var(var, full_pwd))
			return (free(full_pwd), false);
	}
	else
		change_sword(var, full_pwd);
	return (print_error("cd: error retrieving current directory: ", NULL, 0),
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2),
		ft_putstr_fd("No such file or directory\n", 2), true);
}

bool	update_pwd(t_env *var, char *dir)
{
	char	*pwd;
	char	*full_pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (update_pwd_helper(var, dir));
	full_pwd = ft_strjoin("PWD=", pwd);
	free(pwd);
	if (!full_pwd)
		return (false);
	if (env_value_exists("PWD=", var))
	{
		if (!add_var(var, full_pwd))
			return (false);
	}
	else
		change_sword(var, full_pwd);
	return (true);
}
