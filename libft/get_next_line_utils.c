/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 15:43:59 by cproesch          #+#    #+#             */
/*   Updated: 2021/08/09 15:44:31 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_find(char c, char *str)
{
	int	i;

	i = 0;
	if (c == '\0')
	{
		while (str[i])
			i++;
		return (i);
	}
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

void	*ft_memcpyg(char *dst, char *src, int n)
{
	int	i;

	i = 0;
	if ((!src) || (!src[0]))
		return (NULL);
	while (src[i] && (i < n))
	{
		*((unsigned char *)dst + i) = *((unsigned char *)src + i);
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoing(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if ((!s1) && (!s2))
		return (NULL);
	str = malloc(sizeof(char) * (ft_find('\0', s1) + ft_find('\0', s2) + 1));
	if (!str)
		return (ft_del(s1));
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = 0;
	return (str);
}

char	*ft_del(char *str)
{
	free (str);
	str = NULL;
	return (NULL);
}

char	*ft_substrg(char *s, int start, int len)
{
	char	*str;
	int		i;
	int		strlen;

	if (!s)
		return (NULL);
	if (start >= ft_find('\0', s))
		strlen = 0;
	else if (len > (ft_find('\0', s) - start))
		strlen = ft_find('\0', s) - start;
	else
		strlen = len;
	str = (char *)malloc(sizeof(*s) * (strlen + 1));
	if (!str)
		return (ft_del(s));
	i = 0;
	while (s[i] && (i < strlen))
	{
		*(str + i) = *((char *)s + start + i);
		i++;
	}
	*(str + strlen) = 0;
	return (str);
}
