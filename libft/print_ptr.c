/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 17:02:43 by avan-bre          #+#    #+#             */
/*   Updated: 2021/08/09 17:38:10 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_ptr(long unsigned int number, int count)
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
		count = print_ptr(number / 16, count);
		count = print_ptr(number % 16, count);
	}
	return (count);
}
