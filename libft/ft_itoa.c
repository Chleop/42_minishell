/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 18:31:34 by cproesch          #+#    #+#             */
/*   Updated: 2021/06/04 18:32:34 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_digits(int n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n > 9)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char	*ft_filltab(char *tab, int n, int nbdigits)
{
	int	i;
	int	j;

	i = 0;
	if (n < 0)
	{
		tab[i] = '-';
		n = -n;
		i++;
	}
	j = 0;
	while (i < nbdigits)
	{
		tab[nbdigits - 1 - j] = (n % 10) + 48;
		n = n / 10;
		j++;
		i++;
	}
	return (tab);
}

char	*ft_itoa(int n)
{
	char	*tab;
	int		nbdigits;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	nbdigits = ft_count_digits(n);
	tab = (char *)ft_calloc(nbdigits + 1, sizeof(char));
	if (!tab)
		return (NULL);
	return (ft_filltab(tab, n, nbdigits));
}
