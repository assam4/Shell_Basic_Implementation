/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:53:37 by saslanya          #+#    #+#             */
/*   Updated: 2025/01/19 15:53:39 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	s_len;
	char	*ptr;
	size_t	i;

	if (!s || !f)
		return (NULL);
	s_len = ft_strlen(s);
	ptr = (char *)malloc((s_len + 1) * sizeof(char));
	if (ptr)
	{
		i = 0;
		while (i < s_len)
		{
			ptr[i] = f(i, s[i]);
			++i;
		}
		ptr[i] = '\0';
	}
	return (ptr);
}
