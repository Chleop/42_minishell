/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:01:07 by cproesch          #+#    #+#             */
/*   Updated: 2021/05/25 17:01:15 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	unsigned long	n;

	i = 0;
	n = ft_strlen(s);
	if (!(unsigned char)c)
		return ((char *)s + n);
	while (i <= n)
	{
		if (*(s + n - i) == (unsigned char)c)
			return ((char *)s + n - i);
		i++;
	}
	return (0);
}
