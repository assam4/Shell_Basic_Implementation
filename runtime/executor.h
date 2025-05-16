/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:44:43 by saslanya          #+#    #+#             */
/*   Updated: 2025/05/16 09:44:52 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/wait.h>
# include <sys/types.h>
# include <stdio.h>
# include <fcntl.h>
# include "syntax.h"
# include "tree.h"

# define TMP_FILE "/tmp/minishell.tmp"

bool	execute_node(t_ast_node	*node, char **env);
bool	execute_cmd(t_ast_node *node, char **env);
char	*ret_command(char *command, char **env);
char	*get_env_value(char **env, char *key);
char	*get_cmd(t_list *cmd);
void	ft_split_free(char **arr);
bool	set_redirs(t_ast_node *node);
void	print_error(char *mess1, char *mess2, bool flag);

#endif
