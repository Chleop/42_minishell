/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_initialization.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:11:06 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/01 12:19:10 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_end(t_data *data, int i)
{
	if ((data->nr_cmds == 1) || (i == (data->nr_cmds - 1)))
		return (data->nr_token);
	else
		return (data->parser.pipe[i]);
}

int	divide_token(t_data *data, char **token, int *start, int i)
{
	int	j;
	int	len;

	j = 0;
	while (j < data->cmd[i].nr_tok)
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

	i = -1;
	start = 0;
	while (++i < data->nr_cmds)
	{
		end = set_end(data, i);
		data->cmd[i].nr_tok = end - start;
		data->cmd[i].tok = ft_calloc((end - start + 1), sizeof(char *));
		if (!data->cmd[i].tok)
			return (ft_error("Error: malloc failed"));
		if (!divide_token(data, token, &start, i))
			return (0);
		data->cmd[i].param = NULL;
		data->cmd[i].nr_param = 0;
		data->cmd[i].i = NULL;
		data->cmd[i].nr_in = 0;
		data->cmd[i].o = NULL;
		data->cmd[i].nr_out = 0;
		data->cmd[i].type = NULL;
		data->cmd[i].id = i;
		data->cmd[i].data = data;
		data->process_id[i] = 0;
		start++;
	}
	return (1);
}

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
