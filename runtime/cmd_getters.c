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

static char	*ft_join_with_sep(char const *s1, char const *s2, int sep)
{
	char	*str;
	int		len[2];

	if (!s1 || !s2)
		return (NULL);
	len[0] = ft_strlen(s1);
	len[1] = ft_strlen(s2);
	str = ft_calloc(len[0] + len[1] + 2, sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, len[0] + 1);
	str[len[0]] = sep;
	ft_strlcpy(str + len[0] + 1, s2, len[1] + 1);
	return (str);
}

char	*get_env_value(char **env, char *key)
{
	size_t	key_len;
	int		i;

	i = -1;
	key_len = ft_strlen(key);
	while (env[++i])
		if (!ft_strncmp(env[i], key, key_len))
			return (ft_strdup(env[i] + key_len));
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
	i = -1;
	while (splited_path[++i])
	{
		command_path = ft_join_with_sep(splited_path[i], command, '/');
		if (access(command_path, F_OK | X_OK) == EXIT_SUCCESS)
			return (ft_split_free(splited_path), command_path);
		free(command_path);
	}
	ft_split_free(splited_path);
	return (NULL);
}

static char	*get_full_cmd(t_list *cmd, int size)
{
	char	*str_cmd;
	t_list	*iter;
	size_t	len;
	int		i;

	str_cmd = ft_calloc(size + 1, sizeof(char));
	if (!str_cmd)
		return (NULL);
	iter = cmd;
	while (iter)
	{
		len = ft_strlen(str_cmd);
		i = 0;
		while (((t_token *)iter->content)->word[i])
		{
			str_cmd[len + i] = ((t_token *)iter->content)->word[i];
			++i;
		}
		if (iter->next)
			str_cmd[len + i] = ' ';
		else
			str_cmd[len + i] = '\0';
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
	return (get_full_cmd(cmd, size + 1));
}
