/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_struct_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:34:16 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/27 13:52:58 by cproesch         ###   ########.fr       */
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
			if(!add_to_tab(&(data->cmd[cmd_nr].param), &(data->cmd[cmd_nr].nr_param), param))
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

int	set_redirections(t_data *data, char **token, int cmd_nr, int qualif)
{
	if (qualif == RED_IN)
		add_to_tab(&(data->cmd[cmd_nr].i_file), &(data->cmd[cmd_nr].nr_in), *token);
	else if (qualif == HERE_END)
	{
		ft_free(data, token);
		ft_exit (1, "HERE_DOCS NON GERES pour l'instant :)\n");
	}
	else
	{
		add_to_tab(&(data->cmd[cmd_nr].o_file), &(data->cmd[cmd_nr].nr_out), *token);
		if (qualif == RED_OUT_S)
			add_to_int_tab(&(data->cmd[cmd_nr].red_out_type), data->cmd[cmd_nr].nr_out, 1);
		else
			add_to_int_tab(&(data->cmd[cmd_nr].red_out_type), data->cmd[cmd_nr].nr_out, 2);
	}
	return (1);
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
		if(!add_to_tab(&(data->cmd[cmd_nr].param), &(data->cmd[cmd_nr].nr_param), *token))
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
