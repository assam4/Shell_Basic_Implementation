/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 00:37:07 by saslanya          #+#    #+#             */
/*   Updated: 2025/05/19 00:06:07 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static bool	find_env(t_env *var, char *str)
{
	int		i;
	size_t	len;
	char	*temp;

	i = 0;
	len = 0;
	while (str[len] && str[len] != '=')
		++len;
	while (var->env[i])
	{
		if (!ft_strncmp(var->env[i], str, len))
		{
			temp = var->env[i];
			var->env[i] = str;
			return (free(temp), true);
		}
		++i;
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
		if (!var->env[i] && var->env[var->var_count - 2])
		{
			var->env[i] = var->env[var->var_count - 2];
			var->env[var->var_count - 2] = NULL;
			free(var->env + var->var_count);
			--var->var_count;
		}
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
		if (!ft_strncmp(var->env[i], key, ft_strlen(key)))
		{
			free(var->env[i]);
			var->env[i] = NULL;
			env_update(var);
			return (true);
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
			return (false);
		while (var->env[++i])
			new_env[i] = var->env[i];
		new_env[i] = str_cpy;
		free(var->env);
		var->env = new_env;
		++(var->var_count);
	}
	env_update(var);
	return (true);
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
	var->var_count = counter;
	var->env = (char **)ft_calloc(counter + 1, sizeof(char *));
	if (!var->env)
		return (free(var), NULL);
	counter = 0;
	while (def[counter])
		if (!add_var(var, ft_strdup(def[counter++])))
			return (destroy_env(&var), NULL);
	return (var);
}
