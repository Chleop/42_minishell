/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 11:08:20 by avan-bre          #+#    #+#             */
/*   Updated: 2021/08/10 08:25:38 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pick_case(va_list arg_list, char c, int count)
{
	if (c == '%')
		count = count + print_char('%');
	if (c == 'c')
		count = count + print_char(va_arg(arg_list, int));
	if (c == 's')
		count = count + print_string(va_arg(arg_list, char *));
	if (c == 'd' || c == 'i')
		count = count + print_int(va_arg(arg_list, int), 0) - 2;
	if (c == 'u')
		count = count + print_uns_int(va_arg(arg_list, unsigned int), 0) - 2;
	if (c == 'x')
		count = count + print_hex(va_arg(arg_list, unsigned int), 0) - 2;
	if (c == 'X')
		count = count + print_hex_cap(va_arg(arg_list, unsigned int), 0) - 2;
	if (c == 'p')
	{
		write(1, "0x", 2);
		count = count + print_ptr(va_arg(arg_list, long unsigned int), 2) - 2;
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg_list;
	int		index;
	int		count;

	va_start(arg_list, format);
	index = 0;
	count = 0;
	while (format[index])
	{
		if (format[index] != '%')
		{
			ft_putchar_fd(format[index], 1);
			index++;
		}
		else
		{
			if (format[index + 1] == '\0')
				break ;
			else
				count = pick_case(arg_list, format[index + 1], count);
			index = index + 2;
		}
	}
	va_end(arg_list);
	return (index + count);
}
