/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:30:06 by saslanya          #+#    #+#             */
/*   Updated: 2025/04/19 12:30:08 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "get_next_line.h"
# include <stdbool.h>

typedef enum e_token_type
{
	WORD,
	OPERATION,
	REDIRECTION
}	t_token_type;

typedef enum e_operator_type
{
	OP_NONE,
	OP_PIPE,
	OP_AND,
	OP_OR,
	OP_END,
	OP_BACKGROUND,
	OP_SUBSHELL_OPEN,
	OP_SUBSHELL_CLOSE
}	t_operator_type;

typedef enum e_redirection_type
{
	REDIR_NONE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HERE_DOC
}	t_redirection_type;

typedef struct s_token
{
	t_token_type		t_type;
	t_operator_type		o_type;
	t_redirection_type	r_type;
	char				*word;
	bool				is_tmp;
}	t_token;

void	token_free(void *data);
void	set_op_token(const char **line, t_token *token);
void	set_rd_token(const char **line, t_token *token);
void	set_wd_token(const char **line, t_token *token);
bool	get_token(const char **line, t_list **token,
			void (*s)(const char **, t_token *));
bool	ft_isspace(const char *line);
bool	is_operation(const char *line);
bool	is_redirection(const char *line);
bool	get_tokens(const char *line, t_list **tokens);

#endif
