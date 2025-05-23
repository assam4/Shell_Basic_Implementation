/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:47:34 by aadyan            #+#    #+#             */
/*   Updated: 2025/05/23 16:37:51 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	ft_atoi_64(const char *str, int64_t *out)
{
	int			sign;
	int64_t		result;
	int			digit;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if ((sign == 1 && (result > (LLONG_MAX - digit) / 10))
			|| (sign == -1 && (result > (-(LLONG_MIN + digit)) / 10)))
			return (false);
		result = result * 10 + digit;
		str++;
	}
	*out = result * sign;
	return (true);
}

static bool	check_number(char *word, int64_t *num)
{
	int			i;

	i = 0;
	while (word[i])
		if (!ft_isdigit(word[i++]) && word[i] == '-')
			return (false);
	if (ft_strlen(word) > 19)
		return (false);
	if (!ft_atoi_64(word, num))
		return (false);
	return (true);
}

bool	builtin_exit(t_list *cmd, t_env *var)
{
	int64_t	num;

	if (!cmd->next)
		return (g_signal = -1, true);
	cmd = cmd->next;
	if (cmd->next)
	{
		var->exit_status = 1;
		return (print_error("exit\nexit: ", "too many arguments\n", 0), true);
	}
	if (!check_number(((t_token *)cmd->content)->word, &num))
	{
		g_signal = -1;
		var->exit_status = 2;
		return (ft_putstr_fd("exit\nminishell: exit: ", 2),
			ft_putstr_fd(((t_token *)cmd->content)->word, 2),
			ft_putstr_fd(": numeric argument required\n", 2), true);
	}
	g_signal = -1;
	var->exit_status = (int)(unsigned char)num;
	ft_putstr_fd("exit\n", 1);
	return (true);
}
