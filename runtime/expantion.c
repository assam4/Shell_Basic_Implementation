/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:17:59 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/24 23:41:15 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*ft_join_with_free(char *str1, char *str2, char sep)
{
	int		i;
	int		j;
	char	*str;

	str = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 2));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (str1 && str1[i])
		str[j++] = str1[i++];
	str[j++] = sep;
	i = 0;
	while (str2 && str2[i])
		str[j++] = str2[i++];
	str[j] = '\0';
	free(str1);
	return (str);
}

static void	free_split(char ***s)
{
	size_t	i;

	i = 0;
	while ((*s)[i])
	{
		free((*s)[i]);
		++i;
	}
	free(*s);
	*s = NULL;
	return ;
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
	if (!splitted)
		return (NULL);
	all_expanded = ft_strdup(splitted[0]);
	i = 1;
	while (splitted[i])
	{
		if (ft_strchr(splitted[i], '*'))
			expanded = expand_single_wildcard(splitted[i]);
		else
			expanded = ft_strdup(splitted[i]);
		all_expanded = ft_join_with_free(all_expanded, expanded, ' ');
		free(expanded);
		i++;
	}
	free_split(&splitted);
	return (all_expanded);
}
