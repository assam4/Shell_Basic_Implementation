/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:51:10 by saslanya          #+#    #+#             */
/*   Updated: 2025/01/21 23:22:17 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	recursive_output(unsigned int nbr, int fd)
{
	char	letter;

	if (nbr <= 9)
	{
		letter = nbr + '0';
		write(fd, &letter, 1);
		return ;
	}
	else
	{
		recursive_output(nbr / 10, fd);
		letter = nbr % 10 + '0';
		write(fd, &letter, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;

	if (fd <= 0)
		return ;
	if (n < 0)
	{
		write(fd, "-", 1);
		nb = -n;
	}
	else
		nb = n;
	recursive_output(nb, fd);
	return ;
}
