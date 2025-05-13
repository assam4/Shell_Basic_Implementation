/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:55:47 by saslanya          #+#    #+#             */
/*   Updated: 2025/01/19 15:55:49 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_iter;
	const unsigned char	*src_iter;

	dest_iter = (unsigned char *)dest;
	src_iter = (const unsigned char *)src;
	if (!dest_iter && !src_iter)
		return (NULL);
	while (n--)
		*dest_iter++ = *src_iter++;
	return (dest);
}
