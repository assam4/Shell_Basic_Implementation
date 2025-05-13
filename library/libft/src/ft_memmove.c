/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:50:12 by saslanya          #+#    #+#             */
/*   Updated: 2025/01/19 15:50:14 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*iter_dest;

	if (dest != src && n)
	{
		iter_dest = (unsigned char *)dest;
		if (dest < src)
			while (n--)
				*iter_dest++ = *(const unsigned char *)src++;
		else
		{
			iter_dest += n;
			src = (const unsigned char *)src + n;
			while (n--)
				*--iter_dest = *(const unsigned char *)--src;
		}
	}
	return (dest);
}
/*
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*iter_dest;
	const unsigned char	*iter_src;

	if (dest != src)
	{
		iter_dest = (unsigned char *)dest;
		iter_src = (const unsigned char *)src;
		if (dest < src)
			while (n--)
				*iter_dest++ = *iter_src++;
		else
		{
			iter_dest += n;
			iter_src += n;
			while (n--)
				*iter_dest-- = *iter_src--;
		}
	}
	return (dest);
}
*/
