/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uns_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 14:32:39 by avan-bre          #+#    #+#             */
/*   Updated: 2021/08/09 16:38:20 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_uns_int(unsigned int number, int count)
{
	if (number < 10)
	{
		ft_putchar_fd(number + 48, 1);
		count++;
	}
	else
	{
		count = print_uns_int(number / 10, count);
		count = print_uns_int(number % 10, count);
	}
	return (count);
}
