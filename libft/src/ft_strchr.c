/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 23:49:39 by aadyan            #+#    #+#             */
/*   Updated: 2025/03/22 11:40:21 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	while (str && *str)
	{
		if (*str == (char)ch)
			return ((char *)str);
		str++;
	}
	if ((char)ch == '\0')
		return ((char *)str);
	return (NULL);
}
