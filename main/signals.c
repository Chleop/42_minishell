/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:53:55 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/17 18:17:22 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	catch_signal(int sig)
{
	if (g_pid)
	{
		if (sig == SIGINT)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			ft_printf("\n", 1);
			rl_redisplay();
		}
		if (sig == SIGQUIT)
			signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		if (sig == SIGINT)
		{
			kill(1, SIGINT);
			ft_printf("\n", 1);
		}
		if (sig == SIGQUIT)
		{
			kill(1, SIGQUIT);
			ft_printf("Quit (core dumped)\n", 1);
		}
		g_pid = 1;
	}
}

void	signal_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = &catch_signal;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
