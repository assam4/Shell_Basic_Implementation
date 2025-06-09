/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:30:40 by aadyan            #+#    #+#             */
/*   Updated: 2025/06/10 00:33:42 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	replace_chars(char *str, char first, char second)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == first)
			str[index] = second;
		++index;
	}
}

static bool	check_pattern(char *word, char *pattern, int w_i, int p_i)
{
	if (!pattern[p_i])
		return (!word[w_i]);
	if (pattern[p_i] == '"' || pattern[p_i] == '\'')
		return (check_pattern(word, pattern, w_i, p_i + 1));
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
	if (word[w_i] && (word[w_i] == pattern[p_i] || pattern[p_i] == '?'))
		return (check_pattern(word, pattern, w_i + 1, p_i + 1));
	return (false);
}

size_t	ret_size(DIR *dir, char *pattern)
{
	size_t			size;
	struct dirent	*entry;

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
	return (size);
}

static bool	create_expanded(DIR *dir, size_t size,
	char *expanded, char *pattern)
{
	struct dirent	*entry;

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
			replace_chars(entry->d_name, ' ', 1);
			ft_strlcat(expanded, entry->d_name, size);
			ft_strlcat(expanded, " ", size);
		}
	}
	return (true);
}

char	*get_expanded(DIR *dir, char *cmd, size_t size)
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
