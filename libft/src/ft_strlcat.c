/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:05:38 by aadyan            #+#    #+#             */
/*   Updated: 2025/03/22 11:41:00 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	dst_len;

	if (!dst)
		return (0);
	if (size == 0)
		return (ft_strlen(src));
	if (size <= (size_t)ft_strlen(dst))
		return (size + ft_strlen(src));
	dst_len = ft_strlen(dst);
	i = 0;
	while (src[i] && i < size - dst_len - 1)
	{
		dst[dst_len + i] = src[i];
		++i;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + ft_strlen(src));
}
