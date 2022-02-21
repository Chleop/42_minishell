/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_removal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:51:50 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/21 15:19:54 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_c(char *str, int i, char c)
{
	int		*index_tab;
	char	*new_str;

	if (ft_strlen(str) < 2)
		return (NULL);
	index_tab = locate_c_in_string(str + i, c,
			ft_strlen(str) - ft_strlen(str + i));
	new_str = ft_calloc(ft_strlen(str) - 1, sizeof(char));
	if (!new_str)
		return (NULL);
	if (ft_strlen(str) > 2)
		copy_without_tabs(&new_str, index_tab, str);
	free (index_tab);
	return (new_str);
}

int	remove_quotes(char **token)
{
	char	quote;
	char	*temp;
	int		i;

	i = 0;
	quote = is_quoted(*token + i);
	while (quote)
	{
		temp = *token;
		*token = remove_c(*token, i, quote);
		if (!*token)
			return (ft_error2("Error: malloc failed", NULL, 1));
		i = is_paired(quote, temp, i + 1) - 1;
		free (temp);
		temp = NULL;
		if (*token + i)
			quote = is_quoted(*token + i);
		else
			break ;
	}
	return (1);
}

int	if_remove_quotes(char ***tab, int nr_elements)
{
	int		j;

	j = 0;
	while (j < nr_elements)
	{
		remove_quotes(&((*tab)[j]));
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
		if_remove_quotes(&(data->cmd[i].param), data->cmd[i].nr_param);
		if_remove_quotes(&(data->cmd[i].i), data->cmd[i].nr_in);
		if_remove_quotes(&(data->cmd[i].o), data->cmd[i].nr_out);
		i++;
	}
	return (1);
}
