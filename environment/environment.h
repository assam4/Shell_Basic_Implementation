/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 00:32:48 by saslanya          #+#    #+#             */
/*   Updated: 2025/05/29 14:43:11 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "libft.h"
# include <stdbool.h>

# define DEF_SHLVL "SHLVL=1"
# define SHLVL "SHLVL"
# define LEN	5

typedef struct s_env
{
	char	**env;
	int		var_count;
	int		exit_status;
	int		line_count;
}	t_env;

bool	del_var(t_env *var, const char *key);
bool	add_var(t_env *var, char *str_cpy);
t_env	*get_env(char **def);
void	print_env(t_env *var);
void	destroy_env(t_env **var);
void	bump_shlvl(t_env *var);

#endif
