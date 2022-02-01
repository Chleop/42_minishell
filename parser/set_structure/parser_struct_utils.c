/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_struct_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:34:16 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/01 18:23:06 by cproesch         ###   ########.fr       */
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

int	set_command(t_data *data, int n, char **token)
{
	int		i;
	int		j;
	char	*par;

	i = 0;
	j = 0;
	par = NULL;
	while (1)
	{
		if ((((*token)[i] == ' ') || (*token)[i] == '\0'))
		{
			par = ft_substr(*token, j, i - j);
			if (!par)
				return (0);
			if (!add_tab(&(data->cmd[n].param), &(data->cmd[n].nr_param), par))
				return (0);
			free (par);
			if ((*token)[i] == '\0')
				return (1);
			j = i + 1;
		}
		i++;
	}
	return (1);
}

int	set_redirections(t_data *data, char **token, int n, int qualif)
{
	if (qualif == RED_IN)
		add_tab(&(data->cmd[n].i), &(data->cmd[n].nr_in), *token);
	else if (qualif == HERE_END)
	{
		ft_free(data, token);
		final_exit (1, "HERE_DOCS NON GERES pour l'instant :)\n");
	}
	else
	{
		add_tab(&(data->cmd[n].o), &(data->cmd[n].nr_out), *token);
		if (qualif == RED_OUT_S)
			add_int(&(data->cmd[n].type), data->cmd[n].nr_out, 1);
		else
			add_int(&(data->cmd[n].type), data->cmd[n].nr_out, 2);
	}
	return (1);
}

int	classify_token(t_data *data, char **token, int n, int tok_nr)
{
	int	qualif;

	qualif = data->cmd[n].qualif[tok_nr];
	if (qualif == CMD)
	{
		if (!set_command(data, n, token))
			return (0);
		data->cmd[n].qualif[tok_nr] = EMPTY;
	}
	else if (qualif == PARAM)
	{
		if (!add_tab(&(data->cmd[n].param), &(data->cmd[n].nr_param), *token))
			return (0);
		data->cmd[n].qualif[tok_nr] = EMPTY;
	}
	else if ((qualif != OPERATOR) && (qualif != EMPTY))
	{
		set_redirections(data, token, n, qualif);
		data->cmd[n].qualif[tok_nr] = EMPTY;
	}
	return (1);
}
