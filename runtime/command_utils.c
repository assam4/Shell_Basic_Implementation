/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:36:54 by aadyan            #+#    #+#             */
/*   Updated: 2025/06/17 19:30:24 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*ft_join_with_sep(char const *s1, char const *s2, int sep)
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

char	*get_env_value(char *key, char **env)
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

	path = get_env_value("PATH=", env);
	if (!path)
		return (NULL);
	splited_path = ft_split(path, ':');
	free(path);
	if (!splited_path)
		return (NULL);
	if (ft_strchr(command, '/'))
		return (ft_split_free(splited_path), ft_strdup(command));
	i = -1;
	while (splited_path[++i])
	{
		command_path = ft_join_with_sep(splited_path[i], command, '/');
		if (command_path && access(command_path, F_OK | X_OK) == EXIT_SUCCESS)
			return (ft_split_free(splited_path), command_path);
		free(command_path);
	}
	ft_split_free(splited_path);
	return (NULL);
}

static char	*get_full_cmd(t_list *iter, int size)
{
	char	*str_cmd;
	size_t	len;

	if (!iter)
		return (NULL);
	str_cmd = ft_calloc(size + 1, sizeof(char));
	if (!str_cmd)
		return (NULL);
	len = 0;
	while (iter)
	{
		ft_strlcpy(str_cmd + len, ((t_token *)iter->content)->word,
			ft_strlen(((t_token *)iter->content)->word) + 1);
		len = ft_strlen(str_cmd);
		if (iter->next)
			str_cmd[len++] = ' ';
		iter = iter->next;
	}
	return (str_cmd);
}

char	*get_cmd(t_list *cmd, t_env *var)
{
	t_list	*iter;
	size_t	size;

	if (!cmd)
		return (NULL);
	size = 0;
	iter = cmd;
	while (iter)
	{
		if (!((t_token *)iter->content)->is_tmp)
		{
			process_env_expansion(&((t_token *)iter->content)->word,
				var, false);
			expand_wildcard(&((t_token *)iter->content)->word);
			erase_quotes(&((t_token *)iter->content)->word, false, false);
		}
		size += ft_strlen(((t_token *)iter->content)->word) + 1;
		iter = iter->next;
	}
	return (get_full_cmd(cmd, size));
}
