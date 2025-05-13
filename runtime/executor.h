/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 23:46:44 by saslanya          #+#    #+#             */
/*   Updated: 2025/05/14 23:46:44 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/wait.h>
# include <sys/types.h>
# include <stdio.h>
# include <errno.h>
# include "syntax.h"
# include "tree.h"

bool	execute_node(t_ast_node	*node, char **env);
bool	execute_cmd(t_ast_node *node, char **env);
char	*ret_command(char *command, char **env);
char	*get_env_value(char **env, char *key);
char	*get_cmd(t_list *cmd);
void	ft_split_free(char **arr);

#endif
