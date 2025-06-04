/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:31:05 by aadyan            #+#    #+#             */
/*   Updated: 2025/06/04 21:14:47 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# define GREEN	"\001\033[0;32m\002"
# define BLUE	"\001\033[0;34m\002"
# define RESET	"\001\033[0m\002"
# define EXIT	"exit\n"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sysexits.h>
# include "executor.h"
# include "stdbool.h"
# include "environment.h"

void	sig_config(void);
int		print_err(int error);
bool	command_loop(t_list **tokens, t_env *vars);
void	set_exit_status(t_env *vars, int status);
void	handler(int signal);

#endif
