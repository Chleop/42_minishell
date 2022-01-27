/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_struct_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:34:16 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/27 10:40:59 by cproesch         ###   ########.fr       */
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

void	set_redirections(t_data *data, char **token, int cmd_nr, int qualif)
{
	if (qualif == RED_IN)
		data->cmd[cmd_nr].i_file = ft_strdup(*token);
	else if (qualif == HERE_END)
	{
		ft_free(data, token);
		ft_exit (1, "HERE_DOCS NON GERES pour l'instant :)\n");
	}
	else if (qualif == RED_OUT_S)
	{
		data->cmd[cmd_nr].o_file = ft_strdup(*token);
		data->cmd[cmd_nr].red_out_type = 1;
	}
	else if (qualif == RED_OUT_D)
	{
		data->cmd[cmd_nr].o_file = ft_strdup(*token);
		data->cmd[cmd_nr].red_out_type = 2;
	}
}

int	classify_token(t_data *data, char **token, int cmd_nr, int tok_nr)
{
	int	qualif;
	
	qualif = data->cmd[cmd_nr].qualif[tok_nr];
	if (qualif == CMD)
	{
		if (!set_command(data, cmd_nr, token))
			return (0);
		data->cmd[cmd_nr].qualif[tok_nr] = EMPTY;
	}
	else if (qualif == PARAM)
	{
		if(!add_to_params(data, cmd_nr, *token))
			return (0);
		data->cmd[cmd_nr].qualif[tok_nr] = EMPTY;
	}
	else if ((qualif != OPERATOR) && (qualif != EMPTY))
	{
		set_redirections(data, token, cmd_nr, qualif);
		data->cmd[cmd_nr].qualif[tok_nr] = EMPTY;
	}
	return (1);
}
