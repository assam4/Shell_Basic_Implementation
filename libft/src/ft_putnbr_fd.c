/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:29:09 by aadyan            #+#    #+#             */
/*   Updated: 2024/10/11 17:43:13 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	int		n;
	char	c;

	if (nb == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb = -nb;
	}
	n = 1;
	while (nb / n >= 10)
		n *= 10;
	while (n > 0)
	{
		c = (nb / n) + '0';
		ft_putchar_fd(c, fd);
		nb = nb % n;
		n /= 10;
	}
}
