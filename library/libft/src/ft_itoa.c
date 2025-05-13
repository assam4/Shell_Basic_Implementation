/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:47:15 by saslanya          #+#    #+#             */
/*   Updated: 2025/01/19 15:47:17 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	number_len(int n)
{
	size_t	count;

	if (!n)
		return (1);
	count = 0;
	if (n < 0)
		++count;
	while (n)
	{
		++count;
		n /= 10;
	}
	return (count);
}

static size_t	module(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	size_t	nb_len;

	nb_len = number_len(n);
	ptr = (char *)malloc((nb_len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ptr[nb_len] = '\0';
	if (n == 0)
		*ptr = '0';
	else if (n < 0)
		*ptr = '-';
	while (n)
	{
		ptr[--nb_len] = module(n % 10) + '0';
		n /= 10;
	}
	return (ptr);
}
