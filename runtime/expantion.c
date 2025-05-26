/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:17:59 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/26 15:55:27 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static bool	add_to_str(char **dest, char **src)
{
	char	*new_str;

	if (!*src)
		return (free(*dest), *dest = NULL, false);
	new_str = ft_calloc(ft_strlen(*dest) + ft_strlen(*src) + 2, sizeof(char));
	if (!new_str)
		return (free(*dest), *dest = NULL, free(*src), *src = NULL, false);
	ft_strlcpy(new_str, *dest, ft_strlen(*dest) + 1);
	new_str[ft_strlen(new_str)] = ' ';
	ft_strlcpy(new_str + ft_strlen(new_str), *src, ft_strlen(*src) + 1);
	free(*dest);
	free(*src);
	*src = NULL;
	*dest = new_str;
	return (true);
}

static void	smart_free_split(char ***s, int i)
{
	while (i--)
		free((*s)[i]);
	free(*s);
	*s = NULL;
}

static char	*expand_single_wildcard(char *token)
{
	DIR		*dir;
	char	*expanded;
	ssize_t	size;

	dir = opendir(".");
	if (!dir)
		return (perror("minishell: opendir"), NULL);
	size = ret_size(dir, token);
	closedir(dir);
	dir = opendir(".");
	if (!dir)
		return (perror("minishell: opendir"), NULL);
	expanded = get_expanded(dir, token, size);
	closedir(dir);
	return (expanded);
}

char	*expand_wildcard(char *cmd)
{
	char	*expanded;
	char	*all_expanded;
	char	**splitted;
	int		i;

	splitted = ft_split(cmd, ' ');
	i = 0;
	if (!splitted)
		return (NULL);
	all_expanded = splitted[i];
	splitted[i++] = NULL;
	while (splitted[i])
	{
		if (ft_strchr(splitted[i], '*'))
		{
			expanded = expand_single_wildcard(splitted[i]);
			add_to_str(&all_expanded, &expanded);
		}
		else
			add_to_str(&all_expanded, &(splitted[i]));
		if (!all_expanded)
			break ;
		++i;
	}
	return (smart_free_split(&splitted, i), all_expanded);
}
