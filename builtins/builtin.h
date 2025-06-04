/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:25:10 by aadyan            #+#    #+#             */
/*   Updated: 2025/06/04 23:17:57 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "executor.h"
# include "environment.h"
# include "limits.h"

bool	is_builtin(t_list *cmd);
bool	exec_builtin(t_list *cmd, t_env *var);
bool	echo(t_list *cmd);
bool	pwd(t_list *cmd, t_env *var);
bool	cd(t_list *cmd, t_env *var);
bool	env(t_list *cmd, t_env *var);
bool	unset(t_list *cmd, t_env *var);
bool	export(t_list *cmd, t_env *var);
bool	builtin_exit(t_list *cmd, t_env *var);
bool	env_value_exists(char *key, t_env *var);
bool	update_oldpwd(t_env *var, char *oldpwd);
bool	update_pwd_helper(t_env *var, char *dir);
bool	update_pwd(t_env *var, char *dir);

#endif
