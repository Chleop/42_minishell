/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 15:49:50 by cproesch          #+#    #+#             */
/*   Updated: 2021/05/24 15:49:54 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 1;
	if (!src && !dst)
		return (0);
	if (src > dst)
		return (ft_memcpy(dst, src, n));
	while (i <= n)
	{
		*((unsigned char *)dst + n - i) = *((unsigned char *)src + n - i);
		i++;
	}
	return (dst);
}
