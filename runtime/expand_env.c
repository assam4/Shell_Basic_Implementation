/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 00:25:02 by saslanya          #+#    #+#             */
/*   Updated: 2025/06/11 20:09:28 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "stdio.h"

static size_t	calc_length(const char *str, size_t i)
{
	size_t	len;

	len = 0;
	if (!str || !str[i])
		return (len);
	if (str[i] == '?')
		return (++len);
	while (str[i + len])
	{
		if (!len && (ft_isalpha(str[i + len]) || str[i + len] == '_'))
			++len;
		else if (ft_isalnum(str[i + len]) || str[i + len] == '_')
			++len;
		else
			break ;
	}
	return (len);
}

void	expand_env(char **s, size_t *i, size_t len, t_env *var)
{
	size_t	value_len;
	char	*value;
	char	*new_word;

	len = calc_length(*s, *i);
	value = get_value(var, *s + *i, len);
	if (value)
		value_len = ft_strlen(value);
	else
		value_len = 0;
	new_word = ft_calloc(ft_strlen(*s) - len + value_len + 1, sizeof(char));
	if (!new_word)
		return ;
	if (*i - 1 > 0)
		ft_strlcpy(new_word, *s, *i);
	if (value_len)
		ft_strlcpy(new_word + ft_strlen(new_word), value, value_len + 1);
	if ((*s)[*i + len])
		ft_strlcpy(new_word + ft_strlen(new_word), *s + *i + len,
			ft_strlen(*s) - *i - len + 1);
	if ((*s)[*i] == '?')
		free(value);
	*i += value_len - 1;
	free(*s);
	*s = new_word;
}

void	process_env_expansion(char **s, t_env *var, bool expand_single)
{
	size_t	i;
	bool	double_quotes;
	bool	single_quotes;

	if (!*s)
		return ;
	i = 0;
	double_quotes = false;
	single_quotes = false;
	while ((*s)[i])
	{
		if ((*s)[i] == '\'' && !double_quotes)
			single_quotes = !single_quotes;
		else if ((*s)[i] == '"' && !single_quotes)
			double_quotes = !double_quotes;
		if ((*s)[i] == '$'
			&& (!single_quotes || (single_quotes && expand_single)))
		{
			++i;
			expand_env(s, &i, 0, var);
		}
		else
			++i;
	}
}

static size_t	len_without_quotes(const char *s)
{
	size_t	len;
	int		i;
	bool	single_quotes;
	bool	double_quotes;

	single_quotes = false;
	double_quotes = false;
	len = 0;
	i = -1;
	if (!s || !*s)
		return (len);
	while (s[++i])
	{
		if (s[i] == '\'' && !double_quotes)
			single_quotes = !single_quotes;
		else if (s[i] == '"' && !single_quotes)
			double_quotes = !double_quotes;
		else
			++len;
	}
	return (len);
}

void	erase_quotes(char **s, bool single_quotes, bool double_quotes)
{
	char	*new_word;
	size_t	new_len;
	int		oi;
	int		ni;

	new_len = len_without_quotes(*s);
	if (new_len == ft_strlen(*s))
		return ;
	new_word = ft_calloc(new_len + 1, sizeof(char));
	if (!new_word)
		return ;
	oi = -1;
	ni = 0;
	while ((*s)[++oi])
	{
		if ((*s)[oi] == '\'' && !double_quotes)
			single_quotes = !single_quotes;
		else if ((*s)[oi] == '"' && !single_quotes)
			double_quotes = !double_quotes;
		else
			new_word[ni++] = (*s)[oi];
	}
	free(*s);
	*s = new_word;
}
