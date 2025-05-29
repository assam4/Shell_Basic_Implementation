/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:11:57 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/29 22:37:28 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	cd_home(t_env *var)
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
	if (chdir(((t_token *)cmd->next->content)->word) == -1)
		return (print_error("cd: ", NULL, 1), false);
	tmp = ft_strdup(var->secret_pwd + 4);
	if (!tmp)
		return (perror("minishell:"), false);
	if (!update_oldpwd(var, tmp))
		return (print_error("cd: ", NULL, 1), false);
	if (update_pwd(var, ((t_token *)cmd->next->content)->word) == 0)
		return (print_error("cd: ", NULL, 1), false);
	return (true);
}
