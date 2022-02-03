/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 14:38:27 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/03 13:37:39 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_int(int number, int count, int fd)
{
	long int	nr;

	nr = number;
	if (nr < 0)
	{
		ft_putchar_fd('-', fd);
		nr = nr * -1;
		count++;
	}
	if (nr < 10)
	{
		ft_putchar_fd(nr + 48, fd);
		count++;
	}
	else
	{
		count = print_int(nr / 10, count, fd);
		count = print_int(nr % 10, count, fd);
	}
	return (count);
}
