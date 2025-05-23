/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:39:35 by saslanya          #+#    #+#             */
/*   Updated: 2025/05/24 02:10:11 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

volatile sig_atomic_t	g_signal = 0;

static int	sigint_incontinution(void)
{
	if (g_signal == -40)
	{
		rl_replace_line("", 0);
		rl_done = 1;
		g_signal = 0;
	}
	return (EXIT_SUCCESS);
}

static void	handler(int signal)
{
	if (g_signal == -41)
	{
		g_signal = -40;
		return ;
	}
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
	rl_event_hook = sigint_incontinution;
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
	g_signal = -41;
	continution = readline(">");
	if (!continution)
		return (g_signal = 0, true);
	if (g_signal != -41)
		return (free(continution), false);
	g_signal = 0;
	add_history(continution);
	++(vars->line_count);
	if (!get_tokens(continution, &new_tokens))
		return (free(continution), false);
	free(continution);
	ft_lstlast(*tokens)->next = new_tokens;
	return (true);
}
