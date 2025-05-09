/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:51:38 by saslanya          #+#    #+#             */
/*   Updated: 2025/01/19 15:51:40 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	words_calc(const char *s, char c)
{
	size_t	count;
	size_t	is_new;

	count = 0;
	is_new = 1;
	while (*s)
	{
		if (*s != c && is_new)
		{
			is_new = 0;
			++count;
		}
		else if (*s == c && !is_new)
			is_new = 1;
		++s;
	}
	return (count);
}

char	*new_word(const char **s, char c)
{
	char	*end;
	size_t	word_len;
	char	*new_word;

	while (**s == c)
		++*s;
	end = ft_strchr(*s, c);
	if (end)
		word_len = end - *s;
	else
		word_len = ft_strlen(*s);
	new_word = (char *)malloc((word_len + 1) * sizeof(char));
	if (!new_word)
		return (NULL);
	ft_strlcpy(new_word, *s, word_len + 1);
	if (end)
		*s = end;
	return (new_word);
}

static void	free_split(char ***s, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free((*s)[i]);
		++i;
	}
	free(*s);
	*s = NULL;
	return ;
}

char	**ft_split(char const *s, char c)
{
	size_t	count;
	char	**words_ptr;
	size_t	index;

	if (!s)
		return (NULL);
	count = words_calc(s, c) + 1;
	words_ptr = (char **)malloc(count * sizeof(void *));
	if (!words_ptr)
		return (NULL);
	index = 0;
	while (index < count - 1)
	{
		words_ptr[index] = new_word(&s, c);
		if (!words_ptr[index])
		{
			free_split(&words_ptr, index);
			return (NULL);
		}
		++index;
	}
	words_ptr[index] = NULL;
	return (words_ptr);
}
