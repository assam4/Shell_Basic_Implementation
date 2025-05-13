/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:28:41 by saslanya          #+#    #+#             */
/*   Updated: 2025/05/13 21:24:00 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H

# include "token.h"
# include "tree.h"

# define ERR_MESSAGE "minishell: syntax error near unexpected token `"

void	error_message(const t_list *prev, const t_list *tokens);
bool	syntax_analyse(const t_list *tokens);

#endif
