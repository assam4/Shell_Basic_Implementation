/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:17:59 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/31 19:58:00 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

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
	if (size != 0)
		expanded = get_expanded(dir, token, size);
	else
		expanded = ft_strdup(token);
	closedir(dir);
	return (expanded);
}

bool	expand_wildcard(char **cmd)
{
	char	*expanded;

	if (ft_strchr(*cmd, '*'))
	{
		expanded = expand_single_wildcard(*cmd);
		free(*cmd);
		*cmd = expanded;
	}
	return (true);
}
