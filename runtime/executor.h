/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:44:43 by saslanya          #+#    #+#             */
/*   Updated: 2025/06/04 23:56:00 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "syntax.h"
# include "tree.h"
# include "builtin.h"
# include "shell.h"
# include "dirent.h"
# include "termios.h"

# define TMP_FILE "/tmp/minishell.tmp"

typedef struct s_ast_node	t_ast_node;

bool	execute_node(t_ast_node	*node, t_env *vars);
bool	execute_cmd(t_ast_node *node, t_env *vars);
char	*ret_command(char *command, char **env);
char	*get_env_value(char *key, char **env);
char	*get_cmd(t_list *cmd, t_env *var);
void	ft_split_free(char **arr);
bool	set_redirs(t_ast_node *node);
void	child_process(int *fd, int stream);
void	print_error(char *mess1, char *mess2, bool flag);
char	*get_expanded(DIR *dir, char *cmd, ssize_t size);
char	*ft_join_with_sep(char const *s1, char const *s2, int sep);
void	process_env_expansion(char **s, t_env *var);
bool	expand_wildcard(char **cmd);
void	erase_quotes(char **s, bool single_quote, bool double_quote);
ssize_t	ret_size(DIR *dir, char *cmd);
void	replace_chars(char *str, char first, char second);

#endif
