/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_into_structure.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:34:16 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/18 15:21:10 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		while (((*token)[i] && (*token)[i] != quote))
			i++;
		if ((*token)[i])
			i = is_paired(quote, *token, i + 1) + 1;
	}
	return (i);
}

// if the token contains non quoted spaces, then it seperates the token into 
// several parameters
// and adds each parameter to the parameter structure

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

int	set_into_structure1(t_data *data, char **token, int n, int tok_nr)
{
	int	qualif;

	qualif = data->cmd[n].qualif[tok_nr];
	if ((qualif == CMD) || (qualif == PARAM))
	{
		if (!add_tab(&(data->cmd[n].param), &(data->cmd[n].nr_param), *token))
			return (0);
	}
	else if ((qualif != OPERATOR) && (qualif != EMPTY))
		set_redirections_tabs(data, token, n, qualif);
	return (1);
}

int	set_into_structure2(t_data *data, char **token, int n, int tok_nr)
{
	int	qualif;

	qualif = data->cmd[n].qualif[tok_nr];
	if ((qualif == CMD) || (qualif == PARAM))
		set_param2(&(data->cmd[n]), token);
	else if ((qualif != OPERATOR) && (qualif != EMPTY))
		set_redirections_tabs(data, token, n, qualif);
	return (1);
}
