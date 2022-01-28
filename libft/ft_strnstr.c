/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 15:03:34 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/28 13:15:22 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!needle[i])
		return ((char *)haystack);
	while ((i < len) && haystack[i])
	{
		j = 0;
		while ((haystack[i + j] == needle[j]) && ((i + j) < len))
		{
			if (!needle[j + 1])
				return ((char *)haystack + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
