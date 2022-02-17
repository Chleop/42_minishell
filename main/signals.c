/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:53:55 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/17 16:34:15 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	catch_signal(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		ft_printf("\n", 1);
		rl_redisplay();
	}
	//printf("PS1: %s\n", getenv("PS1"));
}

void	signal_handler(int parent)
{
	struct sigaction	sa;
	

	parent = 1;
	sa.sa_handler = &catch_signal;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	// }
	// else
	// {
	// 	// signal(SIGQUIT, SIG_DFL);
	// 	// signal(SIGQUIT, SIG_DFL);
	// }
}
