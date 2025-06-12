/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:50:04 by saslanya          #+#    #+#             */
/*   Updated: 2025/06/13 00:30:06 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include <stdio.h>

char	*get_value(t_env *var, const char *s, size_t len)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (!s[i])
		return ((char *)(s + i - 1));
	if (s[i] == '?')
		return (ft_itoa(var->exit_status));
	while (var->env[i])
	{
		if (!ft_strncmp(var->env[i], s, len)
			&& var->env[i][len] == '=')
			return (ft_strchr(var->env[i], '=') + 1);
		++i;
	}
	return (NULL);
}

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
			if ((*var)->env[i]
				&& ft_strncmp((*var)->env[i], PWD, ft_strlen(PWD)))
				free((*var)->env[i]);
			++i;
		}
	}
	free((*var)->env);
	free((*var)->secret_pwd);
	free(*var);
	*var = NULL;
}

void	change_sword(t_env *var, char *str)
{
	if (str && str != var->secret_pwd)
	{
		free(var->secret_pwd);
		var->secret_pwd = str;
	}
}

void	bump_shlvl(t_env *var)
{
	int		i;

	i = -1;
	while (var->env[++i])
	{
		if (!ft_strncmp(var->env[i], SHLVL, LEN))
		{
			if (update_shlvl(&var->env[i]))
				return ;
			else
				break ;
		}
	}
	add_var(var, ft_strdup(DEF_SHLVL));
}
