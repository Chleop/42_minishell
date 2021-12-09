/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 14:26:31 by cproesch          #+#    #+#             */
/*   Updated: 2021/05/25 17:05:39 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	unsigned long	n;

	i = 0;
	n = ft_strlen(s);
	if (!(char)c)
		return ((char *)s + n);
	if (!s)
		return (0);
	while (i <= n)
	{
		if (*(s + i) == (char)c)
			return ((char *)s + i);
		i++;
	}
	return (0);
}
