/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:39:35 by saslanya          #+#    #+#             */
/*   Updated: 2025/06/09 23:35:07 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

volatile sig_atomic_t	g_signal = DEFAULT;

static int	sigint_incontinution(void)
{
	if (g_signal >= CONT_RPOS || !g_signal)
		return (EXIT_SUCCESS);
	rl_replace_line("", 0);
	rl_done = 1;
	if (g_signal == CRP_HANDLE)
		g_signal = DEFAULT;
	else if (g_signal == SRP_HANDLE)
	{
		rl_on_new_line();
		g_signal = -SIGINT;
	}
	return (EXIT_SUCCESS);
}

void	handler(int signal)
{
	if (g_signal == CONT_RPOS)
	{
		g_signal = CRP_HANDLE;
		return ;
	}
	write(STDOUT_FILENO, "\n", sizeof(char));
	if (g_signal == START_RPOS)
		g_signal = SRP_HANDLE;
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
	g_signal = CONT_RPOS;
	continution = readline(">");
	if (!continution)
		return (g_signal = DEFAULT, true);
	if (g_signal != CONT_RPOS)
		return (vars->exit_status = SIGINT + 128
			, free(continution), false);
	g_signal = EXIT_SUCCESS;
	add_history(continution);
	++(vars->line_count);
	if (!get_tokens(continution, &new_tokens))
		return (free(continution), false);
	free(continution);
	ft_lstlast(*tokens)->next = new_tokens;
	return (true);
}
