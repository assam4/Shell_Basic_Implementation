/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:31:05 by aadyan            #+#    #+#             */
/*   Updated: 2025/06/13 00:29:45 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# define GREEN	"\001\033[0;32m\002"
# define BLUE	"\001\033[0;34m\002"
# define RESET	"\001\033[0m\002"
# define EXIT	"exit\n"
# define START_RPOS -10
# define CONT_RPOS -20
# define SRP_HANDLE -30
# define CRP_HANDLE -40
# define DEFAULT 0

# include "libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sysexits.h>
# include "executor.h"

void	sig_config(void);
int		print_err(int error);
bool	command_loop(t_list **tokens, t_env *vars);
void	set_exit_status(t_env *vars, int status);
void	handler(int signal);
void	content_swap(t_list *left, t_list *right);
bool	update_shlvl(char **lvl);

#endif
