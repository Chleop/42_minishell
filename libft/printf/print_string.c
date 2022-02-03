/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 14:39:34 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/03 13:26:15 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_string(char *string, int fd)
{
	if (string == NULL)
	{
		write(fd, "(null)", 6);
		return (4);
	}
	ft_putstr_fd(string, fd);
	return (ft_strlen(string) - 2);
}
