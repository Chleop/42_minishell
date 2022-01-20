/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:15:14 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/18 18:16:55 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	initialize_data(t_data *data, char **token)
{
	int	nb_pipes;

	data->parser.pipe[0] = 0;
	data->nr_token = count_token(token);
	nb_pipes = localize_pipes(data, token);
	data->nr_cmds = nb_pipes + 1;
	data->cmd = (t_cmd *)ft_calloc(data->nr_cmds + 1, sizeof(t_cmd));
	if (!data->cmd)
		return (ft_error("Error: malloc failed"));
	return (1);
}

int	set_end(t_data *data, int i)
{
	if ((data->nr_cmds == 1) || (i == (data->nr_cmds - 1)))
		return (data->nr_token);
	else
		return (data->parser.pipe[i]);
}

int	divide_token(t_data *data, char **token, int *start, int end, int i)
{
	int	j;
	int	len;

	j = 0;
	while (*start < end)
	{
		len = ft_strlen(token[*start]);
		data->cmd[i].tok[j] = (char *)ft_calloc(len + 1, sizeof(char));
		if (!ft_memcpy(data->cmd[i].tok[j], token[*start], len))
			return (0);
		j++;
		*start = *start + 1;
	}
	return (1);
}

int	initialize_cmds(t_data *data, char **token)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	start = 0;
	while (i < data->nr_cmds)
	{
		end = set_end(data, i);
		data->cmd[i].nr_tok = end - start;
		data->cmd[i].tok = (char **)ft_calloc((end - start + 1), sizeof(char *));
		if (!data->cmd->tok)
			return (ft_error("Error: malloc failed"));
		if (!divide_token(data, token, &start, end, i))
			return (0);
		i++;
		start++;
	}
	return (1);
}
