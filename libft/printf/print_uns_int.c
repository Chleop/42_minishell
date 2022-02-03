/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uns_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 14:32:39 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/03 13:21:50 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_uns_int(unsigned int number, int count, int fd)
{
	if (number < 10)
	{
		ft_putchar_fd(number + 48, fd);
		count++;
	}
	else
	{
		count = print_uns_int(number / 10, count, fd);
		count = print_uns_int(number % 10, count, fd);
	}
	return (count);
}
