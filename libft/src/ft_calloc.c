/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:45:33 by saslanya          #+#    #+#             */
/*   Updated: 2025/01/19 15:45:36 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	size_t	total;
	void	*ptr;

	total = num * size;
	if (num && total / num != size)
		return (NULL);
	ptr = malloc(total);
	if (ptr)
		ft_bzero(ptr, total);
	return (ptr);
}
/* over check */
