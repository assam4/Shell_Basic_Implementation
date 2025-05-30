/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 00:25:02 by saslanya          #+#    #+#             */
/*   Updated: 2025/05/31 02:04:11 by saslanya         ###   ########.fr       */
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

void	expand_env(char **s, size_t *i, char **var)
{
	size_t	len;
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

//	if (*i > 1)
//		ft_strlcpy(new_word, *s, *i);
	printf("%s\n", value);
	if (value_len)
		ft_strlcpy(new_word, value, value_len + 1);
//	if ((*s)[*i + len - 1])
//		ft_strlcpy(new_word + ft_strlen(new_word), *s + *i + len - 1,
//			ft_strlen(*s) - *i - len + 1); 
	*i += value_len;
	free(*s);
	*s = new_word;
}

void	process_env_expansion(char **s, char **var)
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
		if ((*s)[i] == '$' && !single_quotes)
		{
			++i;
			expand_env(s, &i, var);
		}
		else
			++i;
	}
}
