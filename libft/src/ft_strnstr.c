/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:54:08 by saslanya          #+#    #+#             */
/*   Updated: 2025/01/19 15:54:10 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *key, size_t len)
{
	size_t	keylen;

	if (!(*key) || !key)
		return ((char *)str);
	keylen = ft_strlen(key);
	while (*str && len >= keylen)
	{
		if (*str == *key && !(ft_strncmp(str, key, keylen)))
			return ((char *)str);
		++str;
		--len;
	}
	return (NULL);
}
