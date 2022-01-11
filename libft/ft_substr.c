/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 14:40:38 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/11 12:12:47 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	strlen;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		strlen = 0;
	else if (len > (ft_strlen(s) - start))
		strlen = ft_strlen(s) - start;
	else
		strlen = len;
	str = (char *)malloc(sizeof(*s) * (strlen + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] && (i < strlen))
	{
		*(str + i) = *((char *)s + start + i);
		i++;
	}
	str[strlen] = '\0';
	return (str);
}
