/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 14:31:45 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/03 13:19:57 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hex(unsigned int number, int count, int fd)
{
	if (number < 10 )
	{
		ft_putchar_fd(number + 48, fd);
		count++;
	}
	else if (number < 16)
	{
		ft_putchar_fd(number + 87, fd);
		count++;
	}
	else
	{
		count = print_hex(number / 16, count, fd);
		count = print_hex(number % 16, count, fd);
	}
	return (count);
}
