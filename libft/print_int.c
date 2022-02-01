/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 14:38:27 by avan-bre          #+#    #+#             */
/*   Updated: 2021/08/09 18:12:00 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_int(int number, int count)
{
	long int	nr;

	nr = number;
	if (nr < 0)
	{
		ft_putchar_fd('-', 1);
		nr = nr * -1;
		count++;
	}
	if (nr < 10)
	{
		ft_putchar_fd(nr + 48, 1);
		count++;
	}
	else
	{
		count = print_int(nr / 10, count);
		count = print_int(nr % 10, count);
	}
	return (count);
}
