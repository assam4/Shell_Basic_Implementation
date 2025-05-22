/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:39:35 by saslanya          #+#    #+#             */
/*   Updated: 2025/05/22 18:29:57 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

volatile sig_atomic_t	g_signal = 0;

static void	handler(int signal)
{
	g_signal = signal;
	write(STDOUT_FILENO, "\n", sizeof(char));
	rl_replace_line("", 0);
	rl_on_new_line();
//	rl_redisplay();
}

void	sig_config(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}

int	print_err(int error)
{
	ft_putstr_fd(strerror(error), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (error);
}

bool	command_loop(t_list **tokens, t_env *vars)
{
	char	*continution;
	t_list	*new_tokens;

	new_tokens = NULL;
	continution = readline(">");
	if (!continution)
		return (true);
	add_history(continution);
	++(vars->line_count);
	if (!get_tokens(continution, &new_tokens))
		return (free(continution), false);
	free(continution);
	ft_lstlast(*tokens)->next = new_tokens;
	return (true);
}
