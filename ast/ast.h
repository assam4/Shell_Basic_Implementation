/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:46:33 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/07 16:59:09 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "token.h"

typedef struct s_ast_node
{
	t_token				*token;
	struct s_ast_node	*right;
	struct s_ast_node	*left;
	
}	t_ast_node;



#endif