/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:40:32 by saslanya          #+#    #+#             */
/*   Updated: 2025/05/22 12:55:18 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H

# include <sys/wait.h>
# include <sys/types.h>
# include <stdio.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include "token.h"

# define ERR_MESSAGE "minishell: syntax error near unexpected token `"
# define TMP_DIR "/tmp/"

extern int	g_signal;

void	error_message(const t_list *prev, const t_list *tokens);
void	content_swap(t_list *left, t_list *right);
bool	heredoc_exec(t_list *tokens, int i);
bool	syntax_analyse(t_list *tokens);

#endif
