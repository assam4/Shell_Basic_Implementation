/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:50:04 by saslanya          #+#    #+#             */
/*   Updated: 2025/05/19 00:50:07 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

void	print_env(t_env *var)
{
	int	i;

	i = 0;
	if (!var || !var->env)
	{
		 ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	while (var->env[i])
	{
		ft_putstr_fd(var->env[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		++i;
	}
}

void	destroy_env(t_env **var)
{
	int	i;

	i = 0;
	if ((*var)->env)
	{
		while (i <= (*var)->var_count)
		{
			free((*var)->env[i]);
			++i;
		}
	}
	free((*var)->env);
	free(*var);
	*var = NULL;
}
