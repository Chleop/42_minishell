/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 18:12:58 by cproesch          #+#    #+#             */
/*   Updated: 2021/10/20 14:02:38 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(char const *s, char c)
{
	int	i;
	int	nb_words;

	i = 0;
	nb_words = 0;
	while (s[i])
	{
		if ((s[i] != c) && ((s[i + 1] == c) || (s[i + 1] == '\0')))
			nb_words++;
		i++;
	}
	return (nb_words);
}

int	ft_word_len(char const *s, char c)
{
	int	i;

	i = 0;
	while ((s[i] != c) && (s[i] != 0))
		i++;
	return (i);
}

int	if_error(char **tab, int count_word)
{
	if (!tab[count_word])
	{
		count_word = 0;
		while (tab[count_word])
		{
			free (tab[count_word]);
			count_word++;
		}
		return (1);
	}
	return (0);
}

char	**ft_fill_tab(char **tab, char const *s, char c, int nbwords)
{
	int		count_word;
	int		word_len;

	count_word = 0;
	while (count_word < nbwords)
	{
		word_len = 0;
		while ((*s == c) && *s)
			s++;
		word_len = ft_word_len(s, c);
		tab[count_word] = ft_substr(s, 0, word_len);
		if (if_error(tab, count_word))
			return (NULL);
		s = s + word_len;
		count_word++;
	}
	tab[count_word] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		nbwords;

	if (!s)
		return (NULL);
	nbwords = ft_count_words(s, c);
	tab = ft_calloc(nbwords + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	tab = ft_fill_tab(tab, s, c, nbwords);
	if (!tab)
		free (tab);
	return (tab);
}
