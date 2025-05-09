/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 20:57:06 by aadyan            #+#    #+#             */
/*   Updated: 2024/10/21 18:42:34 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d == s)
		return (dest);
	if (s < d)
	{
		i = n;
		while (i > 0)
		{
			--i;
			d[i] = s[i];
		}
		return (dest);
	}
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		++i;
	}
	return (dest);
}
