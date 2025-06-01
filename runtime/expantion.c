/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:17:59 by aadyan            #+#    #+#             */
/*   Updated: 2025/06/01 19:46:50 by aadyan           ###   ########.fr       */
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
	{
		expanded = ft_strdup(token);
		replace_chars(expanded, ' ', 1);
	}
	closedir(dir);
	return (expanded);
}

bool	check_wildcard_position(char *str)
{
	bool	double_quotes;
	bool	single_quotes;
	int		index;

	double_quotes = 0;
	single_quotes = 0;
	index = 0;
	while (str[index])
	{
		if (str[index] == '"' && !single_quotes)
			double_quotes = !double_quotes;
		if (str[index] == '\'' && !double_quotes)
			single_quotes = !single_quotes;
		if (str[index] == '*' || str[index] == '?')
			return (single_quotes || double_quotes);
		++index;
	}
	return (false);
}

bool	expand_wildcard(char **cmd)
{
	char	*expanded;

	if (check_wildcard_position(*cmd))
		return (true);
	if (ft_strchr(*cmd, '*') || ft_strchr(*cmd, '?'))
	{
		expanded = expand_single_wildcard(*cmd);
		if (!expanded)
			return (perror("minishell"), false);
		free(*cmd);
		*cmd = expanded;
	}
	return (true);
}
