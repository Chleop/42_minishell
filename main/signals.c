/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:53:55 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/18 17:32:07 by cproesch         ###   ########.fr       */
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
			ft_printf("\b\b  \b\b", 1);
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
			ft_printf("Quit (core dumped)\n", 1);
			kill(1, SIGQUIT);
		}
		g_pid = 1;
	}
}

void	signal_handler()
{
	struct sigaction	sa;

	sa.sa_handler = &catch_signal;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
