/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:53:55 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/21 12:30:40 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_ignore(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		ft_printf("\n", 1);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
		ft_printf("\b\b  \b\b", 1);
}

void	signal_kill(int sig)
{
	if (sig == SIGINT)
		ft_printf("\n", 1);
	if (sig == SIGQUIT)
		ft_printf("Quit (core dumped)\n", 1);
	g_sig = 0;
}

void	catch_signal(int sig)
{
	if (!g_sig)
		signal_ignore(sig);
	else if (kill(g_sig, sig) == 0)
		signal_kill(sig);
	else
		signal_ignore(sig);
}

void	signal_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = &catch_signal;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
