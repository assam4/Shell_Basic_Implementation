/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:46:33 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/07 20:49:03 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

# include "syntax.h"

typedef struct s_ast_node
{
	t_token				*token;
	struct s_ast_node	*right;
	struct s_ast_node	*left;
	t_list				*cmd;
	t_list				*redir;
}	t_ast_node;

void	tree_blossom(t_ast_node *tree, t_list *tokens);

#endif	