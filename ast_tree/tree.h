/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:46:33 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/09 17:35:09 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

# include <errno.h>
# include "syntax.h"

typedef struct s_ast_node
{
	t_token				*token;
	t_list				*cmd;
	t_list				*redir;
	struct s_ast_node	*right;
	struct s_ast_node	*left;
}	t_ast_node;

void	tree_felling(t_ast_node **tree);
void	get_logic(t_list **prev, t_list *tokens);
void	get_pipe(t_list **prev, t_list *tokens);
bool	create_node(t_ast_node **node, t_list *tokens);
int		get_operator(t_ast_node *tree, t_list *tokens,
			void getter(t_list **, t_list *));
int		tree_blossom(t_ast_node *tree, t_list *tokens);

#endif	
