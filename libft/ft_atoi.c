/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:40:30 by saslanya          #+#    #+#             */
/*   Updated: 2025/01/19 15:40:39 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline int	ft_isspace(char s)
{
	if (s == '\n' || s == '\r' || s == '\t'
		|| s == '\v' || s == ' ' || s == '\f')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	unsigned int	result;
	int				sign;

	sign = 1;
	result = 0;
	while (ft_isspace(*nptr))
		++nptr;
	if (*nptr == '-')
	{
		sign = -1;
		++nptr;
	}
	else if (*nptr == '+')
		++nptr;
	while (*nptr && ft_isdigit(*nptr))
	{
		result = result * 10 + (*nptr - '0');
		++nptr;
	}
	return (sign * result);
}
