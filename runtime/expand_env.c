/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 00:25:02 by saslanya          #+#    #+#             */
/*   Updated: 2025/06/20 00:24:54 by saslanya         ###   ########.fr       */
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

static bool	expand_env(char **s, size_t *i, size_t len, t_env *var)
{
	size_t	value_len;
	char	*value;
	char	*new_word;
	bool	is_spec;

	is_spec = false;
	value_len = 0;
	len = calc_length(*s, *i);
	value = get_value(var, *s + *i, len, &is_spec);
	if (value)
		value_len = ft_strlen(value);
	new_word = ft_calloc(ft_strlen(*s) - len + value_len + 1, sizeof(char));
	if (!new_word)
		return (is_spec);
	if (*i - 1 > 0)
		ft_strlcpy(new_word, *s, *i);
	if (value_len)
		ft_strlcpy(new_word + ft_strlen(new_word), value, value_len + 1);
	if ((*s)[*i + len])
		ft_strlcpy(new_word + ft_strlen(new_word), *s + *i + len,
			ft_strlen(*s) - *i - len + 1);
	if ((*s)[*i] == '?')
		free(value);
	return (*i += value_len - 1, free(*s), *s = new_word, !is_spec);
}

void	process_env_expansion(char **s, t_env *var, bool expand_single)
{
	size_t	i;
	bool	quotes[2];

	if (!*s)
		return ;
	i = 0;
	quotes[0] = false;
	quotes[1] = false;
	while ((*s)[i])
	{
		if ((*s)[i] == '\'' && !quotes[0])
			quotes[1] = !quotes[1];
		else if ((*s)[i] == '"' && !quotes[1])
			quotes[0] = !quotes[0];
		if ((*s)[i] == '$'
			&& (!quotes[1] || (quotes[1] && expand_single)))
		{
			++i;
			if (!expand_env(s, &i, 0, var) && (*s)[i] == '$')
				++i;
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
	int		i[2];

	new_len = len_without_quotes(*s);
	if (new_len == ft_strlen(*s))
		return ;
	new_word = ft_calloc(new_len + 1, sizeof(char));
	if (!new_word)
		return ;
	i[0] = -1;
	i[1] = 0;
	while ((*s)[++i[0]])
	{
		if ((double_quotes || single_quotes) && (*s)[i[0]] == ' ')
			(*s)[i[0]] = 2;
		if ((*s)[i[0]] == '\'' && !double_quotes)
			single_quotes = !single_quotes;
		else if ((*s)[i[0]] == '"' && !single_quotes)
			double_quotes = !double_quotes;
		else
			new_word[i[1]++] = (*s)[i[0]];
	}
	free(*s);
	*s = new_word;
}
