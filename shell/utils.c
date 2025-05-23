/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:39:35 by saslanya          #+#    #+#             */
/*   Updated: 2025/05/24 00:29:21 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

volatile sig_atomic_t	g_signal = 0;

static void	handler(int signal)
{
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", sizeof(char));
	rl_on_new_line();
	if (g_signal == -42)
		rl_redisplay();
	else
		g_signal = signal;
}

void	sig_config(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
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
