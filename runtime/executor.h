/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:44:43 by saslanya          #+#    #+#             */
/*   Updated: 2025/05/23 13:34:26 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "syntax.h"
# include "tree.h"
# include "environment.h"
# include "builtin.h"

# define TMP_FILE "/tmp/minishell.tmp"

bool	execute_node(t_ast_node	*node, t_env *vars);
bool	execute_cmd(t_ast_node *node, t_env *vars);
char	*ret_command(char *command, char **env);
char	*get_env_value(char *key, char **env);
char	*get_cmd(t_list *cmd);
void	ft_split_free(char **arr);
bool	set_redirs(t_ast_node *node);
void	child_process(int *fd, int stream);
void	print_error(char *mess1, char *mess2, bool flag);

#endif
