/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 00:32:48 by saslanya          #+#    #+#             */
/*   Updated: 2025/05/31 01:01:55 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "libft.h"
# include <stdbool.h>

# define DEF_SHLVL "SHLVL=1"
# define SHLVL "SHLVL="
# define PWD "PWD="
# define LEN	6

typedef struct s_env
{
	char	**env;
	char	*secret_pwd;
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
void	change_sword(t_env *var, char *str);
char	*get_value(char **var, const char *s, size_t len);

#endif
