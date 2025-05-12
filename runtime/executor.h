#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/wait.h>
# include <sys/types.h>
# include "syntax.h"

bool	execute_node(t_ast_node	*node);

#endif
