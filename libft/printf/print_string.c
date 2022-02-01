/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 14:39:34 by avan-bre          #+#    #+#             */
/*   Updated: 2021/08/09 18:20:59 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_string(char *string)
{
	if (string == NULL)
	{
		write(1, "(null)", 6);
		return (4);
	}
	ft_putstr_fd(string, 1);
	return (ft_strlen(string) - 2);
}
