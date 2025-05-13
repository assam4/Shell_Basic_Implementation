/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_getters.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:36:54 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/13 22:01:40 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static char	*ft_join_with_sep(char const *s1, char const *s2, char sep)
{
	char	*str;
	int		i;
	int		index;

	if (!s1 || !s2)
		return (NULL);
	str = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 2),
			sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	index = -1;
	while (s1[++i])
		str[++index] = s1[i];
	str[++index] = sep;
	i = -1;
	while (s2[++i])
		str[++index] = s2[i];
	return (str);
}

char	*get_env_value(char **env, char *key)
{
	int	i;

	i = -1;
	while (env[++i])
		if (ft_strncmp(env[i], key, ft_strlen(key)) == 0)
			return (ft_strdup(env[i] + ft_strlen(key)));
	return (NULL);
}

char	*ret_command(char *command, char **env)
{
	char	*command_path;
	int		i;
	char	*path;
	char	**splited_path;

	path = get_env_value(env, "PATH=");
	splited_path = ft_split(path, ':');
	free(path);
	if (ft_strchr(command, '/'))
		return (ft_strdup(command));
	i = 0;
	while (splited_path[i])
	{
		command_path = ft_join_with_sep(splited_path[i], command, '/');
		if (access(command_path, F_OK | X_OK) == 0)
			return (ft_split_free(splited_path), command_path);
		free(command_path);
		i++;
	}
	ft_split_free(splited_path);
	return (NULL);
}

static char	*get_full_cmd(t_list *cmd, int size)
{
	char	*str_cmd;
	t_list	*iter;
	size_t	len;

	str_cmd = ft_calloc(size, sizeof(char));
	if (!str_cmd)
		return (NULL);
	iter = cmd;
	while (iter)
	{
		len = ft_strlen(str_cmd);
		size = -1;
		while (((t_token *)iter->content)->word[++size])
			str_cmd[len + size] = ((t_token *)iter->content)->word[size];
		if (iter->next)
			str_cmd[len + size] = ' ';
		else
			str_cmd[len + size] = '\0';
		iter = iter->next;
	}
	return (str_cmd);
}

char	*get_cmd(t_list *cmd)
{
	t_list	*iter;
	size_t	size;

	size = 0;
	iter = cmd;
	while (iter)
	{
		size += ft_strlen(((t_token *)iter->content)->word) + 1;
		iter = iter->next;
	}
	return (get_full_cmd(cmd, size));
}
