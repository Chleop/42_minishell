/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_struct_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:34:16 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/17 10:43:42 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_redirections(t_data *data, char **token, int n, int qualif)
{
	if (qualif == HERE_END)
	{
		get_here_file(data, token);
		add_tab(&(data->cmd[n].i), &(data->cmd[n].nr_in), data->here_doc);
	}
	else if (qualif == RED_IN)
		add_tab(&(data->cmd[n].i), &(data->cmd[n].nr_in), *token);
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

// Browse the token, if there is a space that is not quoted, put 
// the chars before the space in one param and continue browsing
// i is the current char number
// j is the param starting char

int	increment_quoted_part(int i, char **token)
{
	char	quote;

	quote = is_quoted(*token + i);
	if (quote)
	{
		while ((*token)[i] != quote)
			i++;
		i = is_paired(quote, *token + i, i + 1) + i;
	}
	return (i);
}

// if the token contains non quoted spaces, then it seperates the token into 
// several parameters
// and adds each parameter to the parameter structure

int	set_param1(t_cmd *cmd, char **token)
{
	if (!add_tab(&((*cmd).param), &((*cmd).nr_param), *token))
		return (0);
	return (1);
}

int	set_param2(t_cmd *cmd, char **token)
{
	int		i;
	int		j;
	char	*par;

	i = 0;
	j = 0;
	par = NULL;
	while (1)
	{
		if ((*token)[i])
			i = increment_quoted_part(i, token);
		if ((((*token)[i] == ' ') || (*token)[i] == '\0')
			|| ((*token)[i] == '\n'))
		{
			par = ft_substr(*token, j, i - j);
			if (!par || !add_tab(&((*cmd).param), &((*cmd).nr_param), par))
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

// if the token is a command or a param, set into param table
// otherwise set into redirections tables

int	classify_token1(t_data *data, char **token, int n, int tok_nr)
{
	int	qualif;

	qualif = data->cmd[n].qualif[tok_nr];
	if ((qualif == CMD) || (qualif == PARAM))
		set_param1(&(data->cmd[n]), token);
	else if ((qualif != OPERATOR) && (qualif != EMPTY))
		set_redirections(data, token, n, qualif);
	return (1);
}

int	classify_token2(t_data *data, char **token, int n, int tok_nr)
{
	int	qualif;

	qualif = data->cmd[n].qualif[tok_nr];
	if ((qualif == CMD) || (qualif == PARAM))
		set_param2(&(data->cmd[n]), token);
	else if ((qualif != OPERATOR) && (qualif != EMPTY))
		set_redirections(data, token, n, qualif);
	return (1);
}
