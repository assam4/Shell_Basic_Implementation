#ifndef SYNTAX_H
# define SYNTAX_H

# include "token.h"

# define UN_TOKEN  "minishell: syntax error near unexpected token `"

bool	syntax_analyse(const t_list *tokens);

#endif
