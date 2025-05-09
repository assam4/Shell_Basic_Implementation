/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:49:49 by saslanya          #+#    #+#             */
/*   Updated: 2025/01/19 15:49:51 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	letter;

	letter = (char)c;
	while (n--)
	{
		if (*(char *)s == letter)
			return ((void *)s);
		s = (char *)s + 1;
	}
	return (NULL);
}
