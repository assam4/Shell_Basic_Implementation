/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:40:32 by saslanya          #+#    #+#             */
/*   Updated: 2025/06/19 15:22:36 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H

# include "token.h"
# include "environment.h"
# include "shell.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <stdio.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>

# define ERR_MESSAGE "minishell: syntax error near unexpected token `"
# define TMP_DIR "/tmp/"

extern volatile sig_atomic_t	g_signal;

void	print_warning(char *limiter, t_env *vars);
void	error_message(const t_list *prev, const t_list *tokens);
bool	heredoc_exec(t_list *tokens, int i, t_env *vars);
bool	syntax_analyse(t_list *tokens, t_env *vars);

#endif
