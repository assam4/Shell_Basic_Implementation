/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:53:02 by saslanya          #+#    #+#             */
/*   Updated: 2025/01/19 15:53:04 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dsize)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;
	size_t	result;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (dsize <= dest_len)
		result = dsize + src_len;
	else
		result = dest_len + src_len;
	i = 0;
	while (i < src_len && dest_len + i + 1 < dsize)
	{
		dest[dest_len + i] = src[i];
		++i;
	}
	dest[dest_len + i] = '\0';
	return (result);
}
/* return value */
