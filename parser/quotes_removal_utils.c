/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_removal_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 13:27:08 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/18 15:21:15 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_paired(char q, char *input, int i)
{
	while (input[i])
	{
		if (input[i] == q)
			return (i);
		i++;
	}
	return (0);
}

int	is_quoted(char *token)
{
	int	i;

	i = 0;
	while ((token[i] != '\0') && (token[i] != '\n'))
	{
		if (((token[i] == '\'') || (token[i] == '\"'))
			&& is_paired(token[i], token, i + 1))
			return (token[i]);
		i++;
	}
	return (0);
}

int	*locate_c_in_string(char *token, char c, int len)
{
	int	i;
	int	j;
	int	*index_tab;

	i = 0;
	j = 0;
	while ((token[i]) && c && j < 2)
	{
		if (token[i] == c)
			j++;
		i++;
	}
	index_tab = ft_calloc(j + 1, sizeof(int));
	i = 0;
	j = 0;
	while ((token[i]) && c && j < 2)
	{
		if (token[i] == c)
		{
			index_tab[j] = i + len;
			j++;
		}
		i++;
	}
	return (index_tab);
}

void	copy_without_tabs(char **new_str, int *index_tab, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (i == index_tab[j])
		{
			i++;
			j++;
		}
		if (str[i])
		{
			(*new_str)[i - j] = str[i];
			i++;
		}
	}
}
