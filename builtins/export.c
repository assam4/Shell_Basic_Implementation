/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:16:09 by aadyan            #+#    #+#             */
/*   Updated: 2025/06/03 00:50:06 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static char	*init_key(t_list *cmd, int i)
{
	char	*key;

	key = ft_calloc(i + 2, sizeof(char));
	if (!key)
		return (false);
	i = 0;
	while (((t_token *)cmd->content)->word[i]
		&& ((t_token *)cmd->content)->word[i] != '+')
	{
		key[i] = ((t_token *)cmd->content)->word[i];
		++i;
	}
	key[i] = '=';
	return (key);
}

static bool	append_value(t_list *cmd, t_env *var)
{
	char	*key;
	char	*value;
	char	*full_value;
	char	*env_val;
	int		i;

	i = 0;
	while (((t_token *)cmd->content)->word[i]
		&& ((t_token *)cmd->content)->word[i] != '+')
		++i;
	key = init_key(cmd, i);
	value = get_env_value(key, var->env);
	full_value = ft_strjoin(value,
			ft_strchr(((t_token *)cmd->content)->word, '=') + 1);
	if (!full_value)
		return (free(key), free(value), false);
	env_val = ft_strjoin(key, full_value);
	if (!env_val)
		return (free(key), free(value), free(full_value), false);
	key[ft_strlen(key) - 1] = 0;
	if (!add_var(var, env_val))
		return (free(key), free(full_value), free(value), false);
	return (free(key), free(full_value), free(value), true);
}

static void	print_export(t_env *var)
{
	int		i;
	char	**value;

	i = 0;
	if (!var || !var->env)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	while (var->env[i])
	{
		value = ft_split(var->env[i], '=');
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(value[0], STDOUT_FILENO);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		if (value[1])
			ft_putstr_fd(value[1], STDOUT_FILENO);
		ft_putstr_fd("\"\n", STDOUT_FILENO);
		ft_split_free(value);
		++i;
	}
}

bool	export(t_list *cmd, t_env *var)
{
	char	*eval;
	char	*plus;
	char	*word;

	if (!cmd->next)
		return (print_export(var), true);
	cmd = cmd->next;
	while (cmd)
	{
		word = ((t_token *)cmd->content)->word;
		eval = ft_strchr(word, '=');
		plus = ft_strchr(word, '+');
		if (word == eval || word == plus || (plus && !eval))
			return (ft_putstr_fd("minishell: export: ", 2),
				ft_putstr_fd(word, 2),
				ft_putstr_fd(": not a valid identifier\n", 2), false);
		if (!plus && eval && !add_var(var, ft_strdup(word)))
			return (false);
		else if (plus && eval && !append_value(cmd, var))
			return (false);
		cmd = cmd->next;
	}
	return (true);
}
