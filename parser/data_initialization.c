/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_initialization.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:11:06 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/21 15:04:07 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_strings(char **token)
{
	int	i;

	i = 0;
	while (token[i])
		i++;
	return (i);
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

int	initialize_data(t_data *data, char **token)
{
	int	nb_pip;

	data->nr_token = count_strings(token);
	data->pipe_index = locate_pipes(token);
	nb_pip = 0;
	while (data->pipe_index[nb_pip])
		nb_pip++;
	data->nr_cmds = nb_pip + 1;
	data->cmd = (t_cmd *)ft_calloc(data->nr_cmds, sizeof(t_cmd));
	if (!data->cmd)
		return (ft_error2("Error: malloc failed", NULL, 1));
	return (1);
}
