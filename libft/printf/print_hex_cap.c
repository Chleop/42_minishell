/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex_cap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 17:57:27 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/21 15:55:56 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hex_cap(unsigned int number, int count, int fd)
{
	if (number < 10)
	{
		ft_putchar_fd(number + 48, fd);
		count++;
	}
	else if (number < 16)
	{
		ft_putchar_fd(number + 55, fd);
		count++;
	}
	else
	{
		count = print_hex_cap(number / 16, count, fd);
		count = print_hex_cap(number % 16, count, fd);
	}
	return (count);
}
