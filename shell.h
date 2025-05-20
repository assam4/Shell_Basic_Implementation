/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:31:05 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/21 16:01:44 by aadyan           ###   ########.fr       */
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

#endif
