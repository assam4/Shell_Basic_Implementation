/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:53:49 by saslanya          #+#    #+#             */
/*   Updated: 2025/01/19 15:53:51 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n--)
	{
		if (!*s1 || !*s2 || *s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		++s1;
		++s2;
	}
	return (0);
}
