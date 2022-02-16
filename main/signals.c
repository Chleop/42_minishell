/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:53:55 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/16 13:16:06 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	catch_signal(int sig)
{
	//with this I wanted to display a new prompt, but I have no clue how. 
	//I think the problem is that I don't put the right function
	//at the right place in the code....
	if (sig == SIGINT)
	{
		printf(" We want a new prompt!\n");
		rl_redisplay();
	}
	else
	{
		signal(sig, SIG_IGN);
		printf(" WHYYY does it still print the signal?\n");
	}
}

void	handle_signals(int sig)
{
	//At one point this worked, but not anymore....	
	if (sig == SIGQUIT)
		exit (130);
	else
		signal(sig, SIG_IGN);
}

void	signal_handler(int parent)
{
	struct sigaction	sa;
	sigset_t 			set;

	// printf("Signal: %d\n", SIGINT);
	// printf("Signal: %d\n", SIGQUIT);
	// sa.sa_flags = 0;
	// if (parent)
	// 	sa.sa_handler = &catch_signal;
	// else
	// 	sa.sa_handler = &handle_signals;
	// sigaction(SIGINT, &sa, NULL);
	// sigaction(SIGQUIT, &sa, NULL);
	if (parent)
	{
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sa.sa_handler = catch_signal;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
		sigaddset(&set, SIGQUIT);
		sigaddset(&set, SIGINT);
	}
	else
	{
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sa.sa_handler = handle_signals;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
		sigaddset(&set, SIGQUIT);
		sigaddset(&set, SIGINT);
	}
}
