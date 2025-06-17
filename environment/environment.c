/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 00:37:07 by saslanya          #+#    #+#             */
/*   Updated: 2025/06/17 15:56:51 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static bool	find_env(t_env *var, char *str)
{
	int		i;

	i = -1;
	if (!str)
		return (false);
	while (var->env[++i])
	{
		if (ft_strchr(str, '=')
			&& !ft_strncmp(var->env[i], str, ft_strchr(str, '=') - str))
		{
			free(var->env[i]);
			var->env[i] = str;
			if (!ft_strncmp(var->env[i], PWD, ft_strlen(PWD)))
				var->secret_pwd = var->env[i];
			return (true);
		}
		else if (!ft_strncmp(var->env[i], str, ft_strlen(str)))
			return (free(str), true);
	}
	return (false);
}

static void	env_update(t_env *var)
{
	int		i;
	char	*temp;

	i = 0;
	while (var->env[i + 1])
	{
		if (var->env[i + 1] && ft_strncmp(var->env[i], var->env[i + 1],
				ft_strlen(var->env[i])) > 0)
		{
			temp = var->env[i];
			var->env[i] = var->env[i + 1];
			var->env[i + 1] = temp;
			i = 0;
		}
		else
			++i;
	}
}

bool	del_var(t_env *var, const char *key)
{
	int		i;

	i = 0;
	if (!var)
		return (false);
	while (var->env[i])
	{
		if (!ft_strncmp(var->env[i], key, ft_strlen(key))
			&& var->env[i][ft_strlen(key)] == '=')
		{
			if (ft_strncmp(var->env[i], PWD, ft_strlen(PWD)))
				free(var->env[i]);
			var->env[i] = NULL;
			if (var->var_count != 1)
			{
				var->env[i] = var->env[var->var_count - 1];
				var->env[var->var_count - 1] = NULL;
				--var->var_count;
			}
			return (env_update(var), true);
		}
		else
			++i;
	}
	return (false);
}

bool	add_var(t_env *var, char *str_cpy)
{
	char	**new_env;
	int		i;

	if (!str_cpy)
		return (false);
	if (!find_env(var, str_cpy))
	{
		i = -1;
		new_env = ft_calloc(var->var_count + 2, sizeof(char *));
		if (!new_env)
			return (free(str_cpy), false);
		while (var->env[++i])
			new_env[i] = var->env[i];
		new_env[i] = str_cpy;
		if (!ft_strncmp(str_cpy, PWD, ft_strlen(PWD)))
		{
			free(var->secret_pwd);
			var->secret_pwd = str_cpy;
		}
		free(var->env);
		var->env = new_env;
		++(var->var_count);
	}
	return (env_update(var), true);
}

t_env	*get_env(char **def)
{
	t_env	*var;
	int		counter;

	var = ft_calloc(1, sizeof(t_env));
	if (!var)
		return (NULL);
	counter = 0;
	while (def[counter])
		++counter;
	var->env = (char **)ft_calloc(counter + 1, sizeof(char *));
	if (!var->env)
		return (free(var), NULL);
	counter = 0;
	while (def[counter])
		if (!add_var(var, ft_strdup(def[counter++])))
			return (destroy_env(&var), NULL);
	bump_shlvl(var);
	check_secret_pwd(&var->secret_pwd);
	return (var);
}
