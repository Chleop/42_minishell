/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_struct_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:34:16 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/26 18:10:58 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quoted(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (((token[i] == '\'') || (token[i] == '\"'))
		&& is_paired(token[i], token, i + 1))
			return (token[i]);
		i++;
	}
	return (0);
}

int	add_to_params(t_data *data, int cmd_nr, char *param)
{
	char	**temp;
	int		l;

	data->cmd[cmd_nr].nr_param++;
	temp = data->cmd[cmd_nr].param;
	data->cmd[cmd_nr].param = (char **)ft_calloc(data->cmd[cmd_nr].nr_param + 1, sizeof(char *));
	if (!data->cmd[cmd_nr].param)
		return (0);
	if (temp)
	{
		l = 0;
		while (temp[l])
		{
			data->cmd[cmd_nr].param[l] = ft_strdup(temp[l]);
			free (temp[l]);
			l++;
		}
		free(temp);
		if (!data->cmd[cmd_nr].param[l - 1])
			return (0);
	}
	data->cmd[cmd_nr].param[data->cmd[cmd_nr].nr_param - 1] = ft_strdup(param);
	if (!data->cmd[cmd_nr].param[data->cmd[cmd_nr].nr_param - 1])
		return (0);
	data->cmd[cmd_nr].param[data->cmd[cmd_nr].nr_param] = NULL;
	return (1);
}

int	set_command(t_data *data, int cmd_nr, char **token)
{
	int		i;
	int		j;
	char	*param;

	i = 0;
	j = 0;
	param = NULL;
	while (1)
	{
		if ((((*token)[i] == ' ') || (*token)[i] == '\0'))
		{
			param = ft_substr(*token, j, i);
			if (!param)
				return (0);
			if(!add_to_params(data, cmd_nr, param))
				return (0);
			free (param);
			if ((*token)[i] == '\0')
				return (1);
			j = i + 1;
		}
		i++;
	}
	return (1);
}

int	tidy_token(t_data *data, char **token, int cmd_nr, int tok_nr)
{
	if (data->cmd[cmd_nr].qualif[tok_nr] == CMD)
	{
		if (!set_command(data, cmd_nr, token))
			return (0);
		data->cmd[cmd_nr].qualif[tok_nr] = EMPTY;
	}
	else if (data->cmd[cmd_nr].qualif[tok_nr] == PARAM)
	{
		if(!add_to_params(data, cmd_nr, data->cmd[cmd_nr].tok[tok_nr]))
			return (0);
		data->cmd[cmd_nr].qualif[tok_nr] = EMPTY;
	}
	return (1);
}
