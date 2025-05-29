/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:50:04 by saslanya          #+#    #+#             */
/*   Updated: 2025/05/29 14:43:00 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

void	print_env(t_env *var)
{
	int	i;

	i = 0;
	if (!var || !var->env)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	while (var->env[i])
	{
		ft_putstr_fd(var->env[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		++i;
	}
}

void	destroy_env(t_env **var)
{
	int	i;

	i = 0;
	if ((*var)->env)
	{
		while (i <= (*var)->var_count)
		{
			free((*var)->env[i]);
			++i;
		}
	}
	free((*var)->env);
	free(*var);
	*var = NULL;
}

void	bump_shlvl(t_env *var)
{
	char	*lvl_str;
	int		i;

	i = -1;
	while (var->env[++i])
	{
		if (!ft_strncmp(var->env[i], SHLVL, LEN)
			&& var->env[i][LEN] == '=')
		{
			lvl_str = ft_itoa(ft_atoi(var->env[i] + LEN + 1) + 1);
			if (!lvl_str)
				return ;
			free(var->env[i]);
			var->env[i] = ft_calloc(LEN + ft_strlen(lvl_str) + 2, sizeof(char));
			if (!var->env[i])
				return ;
			ft_strlcpy(var->env[i], SHLVL, LEN + 1);
			var->env[i][LEN] = '=';
			ft_strlcpy(var->env[i] + LEN + 1, lvl_str, ft_strlen(lvl_str) + 1);
			free(lvl_str);
			return ;
		}
	}
	add_var(var, ft_strdup(DEF_SHLVL));
}
