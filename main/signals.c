/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:53:55 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/14 17:10:44 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(int sig)
{
	if (sig == SIGQUIT)
		return ;
	else if (sig == SIGINT)
	{
		printf("Sigint\n");
		return ;
	}
}

void	signal_handler(t_data *data)
{
	struct sigaction	sa;
	
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &handle_signals;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	printf("%d\n", data->exit_code);
}
