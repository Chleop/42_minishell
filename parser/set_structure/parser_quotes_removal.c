/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes_removal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:51:50 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/16 18:27:44 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*locate_c_in_string(char *token, char c)
{
	int	i;
	int	j;
	int	*index_tab;

	i = 0;
	j = 0;
	while ((token[i]) && c)
	{
		if (token[i] == c)
			j++;
		i++;
	}
	index_tab = ft_calloc(j + 1, sizeof(int));
	i = 0;
	j = 0;
	while (token[i] && c)
	{
		if (token[i] == c)
		{
			index_tab[j] = i;
			j++;
		}
		i++;
	}
	return (index_tab);
}

int	*locate_pipes(char **token)
{
	int	i;
	int	j;
	int	*index_tab;

	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i][0] == '|')
			j++;
		i++;
	}
	index_tab = ft_calloc(j + 1, sizeof(int));
	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i][0] == '|')
		{
			index_tab[j] = i;
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

void	add_quotes(char **param, char *quote)
{
	char	*temp;

	temp = *param;
	*param = ft_strjoin(quote, *param);
	free(temp);
	temp = *param;
	*param = ft_strjoin(*param, quote);
	free(temp);
}

char	*remove_c(char *str, char c)
{
	int		*index_tab;
	char	*new_str;

	if (ft_strlen(str) < 2)
		return (NULL);
	index_tab = locate_c_in_string(str, c);
	printf("indextab[0] = %d, indextab[1] = %d\n", index_tab[0], index_tab[1]);
	new_str = ft_calloc(ft_strlen(str) - 1, sizeof(char));
	if (!new_str)
		return (NULL);
	if (ft_strlen(str) > 2)
		copy_without_tabs(&new_str, index_tab, str);
	free (index_tab);
	return (new_str);
}

int	remove_quotes(char **token, t_data *data)
{
	char	quote;
	char	*temp;

	quote = is_quoted(*token);
	while (quote)
	{
		temp = *token;
		*token = remove_c(*token, quote);
		if (!*token)
			return (ft_error2("Error: malloc failed", NULL, data, 1));
		free (temp);
		temp = NULL;
		quote = is_quoted(*token);
	}
	return (1);
}

