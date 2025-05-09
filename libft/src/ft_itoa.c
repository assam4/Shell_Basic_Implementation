/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:26:50 by aadyan            #+#    #+#             */
/*   Updated: 2025/01/25 18:24:09 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = src[i];
	return (dest);
}

static int	get_len(int nb)
{
	int	n;
	int	count;

	n = 1;
	count = 0;
	if (nb < 0)
	{
		if (nb == -2147483648)
			return (11);
		nb = -nb;
		++count;
	}
	while (nb / n >= 10)
	{
		n *= 10;
		++count;
	}
	return (count + 1);
}

static char	*get_num(char *num, int nb, int n, int i)
{
	if (nb == -2147483648)
	{
		ft_strcpy(num, "-2147483648");
		return (num);
	}
	while (n > 0)
	{
		num[i] = (nb / n) + '0';
		nb = nb % n;
		n /= 10;
		i++;
	}
	num[i] = 0;
	return (num);
}

char	*ft_itoa(int nb)
{
	int		n;
	int		i;
	char	*num;

	num = (char *)malloc((get_len(nb) + 1) * sizeof(char));
	if (!num)
		return (NULL);
	i = 0;
	if (nb < 0)
	{
		num[i] = '-';
		i++;
		nb = -nb;
	}
	n = 1;
	while (nb / n >= 10)
		n *= 10;
	num = get_num(num, nb, n, i);
	return (num);
}
