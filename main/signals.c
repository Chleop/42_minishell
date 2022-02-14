/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:53:55 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/14 13:41:17 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sgkill(int sig)
{
	if (sig == SIGQUIT)
		return ;
}

void	handle_sgint(int sig)
{
	printf("Sig is: %d\n", sig);
}

void	signal_handler(t_data *data)
{
	struct sigaction	sa;
	struct sigaction	sb;
	

	sa.sa_handler = &handle_sgkill;
	sb.sa_handler = &handle_sgint;
//	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sb, NULL);
	printf("%d\n", data->exit_code);
}