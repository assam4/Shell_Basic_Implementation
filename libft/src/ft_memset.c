/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 20:57:42 by aadyan            #+#    #+#             */
/*   Updated: 2024/10/17 23:07:47 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	size_t			i;
	unsigned char	*p;

	p = ptr;
	i = 0;
	while (i < num)
	{
		p[i++] = value;
	}
	return (ptr);
}
