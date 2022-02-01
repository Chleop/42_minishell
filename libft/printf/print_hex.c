/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 14:31:45 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/01 16:25:51 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hex(unsigned int number, int count)
{
	if (number < 10 )
	{
		ft_putchar_fd(number + 48, 1);
		count++;
	}
	else if (number < 16)
	{
		ft_putchar_fd(number + 87, 1);
		count++;
	}
	else
	{
		count = print_hex(number / 16, count);
		count = print_hex(number % 16, count);
	}
	return (count);
}
