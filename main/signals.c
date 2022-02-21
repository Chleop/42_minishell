/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:53:55 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/21 15:19:28 by cproesch         ###   ########.fr       */
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
		g_lobal.exit_code = 130;
	}
	if (sig == SIGQUIT)
		ft_printf("\b\b  \b\b", 1);
}

void	signal_kill(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n", 1);
		g_lobal.exit_code = 130;
	}
	if (sig == SIGQUIT)
	{
		ft_printf("Quit (core dumped)\n", 1);
		g_lobal.exit_code = 131;
	}
	g_lobal.g_sig = 0;
}

void	catch_signal(int sig)
{
	if (!g_lobal.g_sig)
		signal_ignore(sig);
	else if (kill(g_lobal.g_sig, sig) == 0)
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
