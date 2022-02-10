/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes_removal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:51:50 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/10 13:04:17 by cproesch         ###   ########.fr       */
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
		if (i == index_tab[j])
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

char	*remove_c(char *str, char c)
{
	int		*index_tab;
	char	*new_str;

	if (ft_strlen(str) < 2)
		return (NULL);
	index_tab = locate_c_in_string(str, c);
	new_str = ft_calloc(ft_strlen(str) - 1, sizeof(char));
	if (!new_str)
		return (NULL);
	if (ft_strlen(str) > 2)
		copy_without_tabs(&new_str, index_tab, str);
	free (index_tab);
	return (new_str);
}

int	if_remove_quotes(char ***tab, int nr_elements, t_data *data)
{
	char	quote;
	char	*temp;
	int		j;

	j = 0;
	while (j < nr_elements)
	{
		quote = is_quoted((*tab)[j]);
		if (quote)
		{
			temp = (*tab)[j];
			(*tab)[j] = remove_c((*tab)[j], quote);
			if (!(*tab)[j])
				return (ft_error2("Error: malloc failed", NULL, data, 1));
			free (temp);
			temp = NULL;
		}
		j++;
	}
	return (1);
}

int	remove_quotes_inside_struct(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_cmds)
	{
		if_remove_quotes(&(data->cmd[i].param), data->cmd[i].nr_param, data);
		if_remove_quotes(&(data->cmd[i].i), data->cmd[i].nr_in, data);
		if_remove_quotes(&(data->cmd[i].o), data->cmd[i].nr_out, data);
		i++;
	}
	return (1);
}
