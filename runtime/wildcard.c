/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:30:40 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/31 19:58:51 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static char	*get_pattern(char *cmd)
{
	int		i;
	int		start;
	int		end;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '*')
		{
			start = i;
			while (start > 0 && cmd[start - 1] != ' ')
				start--;
			end = i;
			while (cmd[end] && cmd[end] != ' ')
				end++;
			return (ft_substr(cmd, start, end - start));
		}
		i++;
	}
	return (NULL);
}

static bool	check_pattern(char *word, char *pattern, int w_i, int p_i)
{
	if (!pattern[p_i])
		return (!word[w_i]);
	if (pattern[p_i] == '*')
	{
		while (word[w_i])
		{
			if (check_pattern(word, pattern, w_i, p_i + 1))
				return (true);
			w_i++;
		}
		return (check_pattern(word, pattern, w_i, p_i + 1));
	}
	else if (word[w_i] == pattern[p_i])
		return (check_pattern(word, pattern, w_i + 1, p_i + 1));
	else
		return (false);
}

ssize_t	ret_size(DIR *dir, char *cmd)
{
	ssize_t			size;
	struct dirent	*entry;
	char			*pattern;

	pattern = get_pattern(cmd);
	if (!pattern)
		return (-1);
	size = 0;
	while (true)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (ft_strncmp(entry->d_name, ".",
				ft_strlen(entry->d_name) + 1) == 0
			|| ft_strncmp(entry->d_name, "..",
				ft_strlen(entry->d_name) + 1) == 0)
			continue ;
		if (check_pattern(entry->d_name, pattern, 0, 0))
			size += ft_strlen(entry->d_name) + 1;
	}
	return (free(pattern), size);
}

static bool	create_expanded(DIR *dir, ssize_t size, char *expanded, char *cmd)
{
	struct dirent	*entry;
	char			*pattern;

	pattern = get_pattern(cmd);
	if (!pattern)
		return (false);
	while (true)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (ft_strncmp(entry->d_name, ".",
				ft_strlen(entry->d_name) + 1) == 0
			|| ft_strncmp(entry->d_name, "..",
				ft_strlen(entry->d_name) + 1) == 0)
			continue ;
		if (check_pattern(entry->d_name, pattern, 0, 0))
		{
			ft_strlcat(expanded, entry->d_name, size);
			ft_strlcat(expanded, " ", size);
		}
	}
	return (free(pattern), true);
}

char	*get_expanded(DIR *dir, char *cmd, ssize_t size)
{
	char	*expanded;

	expanded = ft_calloc(size, sizeof(char));
	if (!expanded)
		return (NULL);
	create_expanded(dir, size, expanded, cmd);
	if (!*expanded)
	{
		free(expanded);
		return (cmd);
	}
	return (expanded);
}
