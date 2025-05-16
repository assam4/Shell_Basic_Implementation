/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:25:10 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/16 20:44:45 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "tree.h"
# include "executor.h"

bool	is_builtin(t_list *cmd);
bool	exec_builtin(t_list *cmd);
bool	echo(t_list *cmd);
bool	pwd(t_list *cmd);
bool	cd(t_list *cmd);

#endif