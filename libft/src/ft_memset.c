/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:50:27 by saslanya          #+#    #+#             */
/*   Updated: 2025/01/19 15:50:28 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int simb, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)ptr;
	while (n--)
		*p++ = (unsigned char)simb;
	return (ptr);
}
