/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex_cap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 17:57:27 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/01 16:26:02 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hex_cap(unsigned int number, int count)
{
	if (number < 10 )
	{
		ft_putchar_fd(number + 48, 1);
		count++;
	}
	else if (number < 16)
	{
		ft_putchar_fd(number + 55, 1);
		count++;
	}
	else
	{
		count = print_hex_cap(number / 16, count);
		count = print_hex_cap(number % 16, count);
	}
	return (count);
}
