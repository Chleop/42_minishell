/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 12:37:34 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/03 13:34:15 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

int	    ft_printf(const char *format, int fd, ...);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
int		print_char(int c, int fd);
int		print_string(char *string, int fd);
int		print_int(int i, int count, int fd);
int		print_uns_int(unsigned int number, int count, int fd);
int		print_hex(unsigned int i, int count, int fd);
int		print_hex_cap(unsigned int i, int count, int fd);
int		print_ptr(long unsigned int number, int count, int fd);

#endif
