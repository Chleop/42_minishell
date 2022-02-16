/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:53:55 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/16 18:43:38 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	catch_signal(int sig)
{
	//with this I wanted to display a new prompt, but I have no clue how. 
	//I think the problem is that I don't put the right function
	//at the right place in the code....
	if (sig == SIGINT)
	// {
		// printf("Inside catch signal\n");
		// printf(PURPLE "\b\b  \b\b\nour_minishell:~$ " RESET);
		printf(PURPLE "\nour_minishell:~$ " RESET);
		// rl_redisplay();
	// }
	// else
	// {
	// 	signal(sig, SIG_IGN);
	// 	printf(" WHYYY does it still print the signal?\n");
	// }
}

// void	handle_signals(int sig)
// {
// 	//At one point this worked, but not anymore....	
// 	if (sig == SIGQUIT)
// 		exit (130);
// 	else
// 		signal(sig, SIG_IGN);
// }

void	signal_handler(int parent)
{
	//I've tried this function with sigaction, signal,
	//sigemptyset + sigaddset and combinations of those. Nothing works. 
	//Even the child/parent thing doesn't work, because apparently
	//when we are in the child (in a infinite command), the
	//program is still executing catch_signal in stead of handle_signals.
	
	//sigset_t			set;
	// struct sigaction	sa;
	//this sets the struct for sigaction

	parent = 1;
	// if (parent)
	// {
		// sa.sa_handler = catch_signal;
		// sigemptyset(&sa.sa_mask);
		// sa.sa_flags = 0;
		// sa.sa_flags = SA_RESTART;
		// sigaction(SIGINT, &sa, NULL);
		signal(SIGINT, catch_signal);
		// return ;
	// }
	//after you have to set every key you want handled with the handler
	// if (parent)
	// 	printf("Exit code: %d\n", data->exit_code);
	//This was just to silence the 'unused variable data' error
	return ;
}

