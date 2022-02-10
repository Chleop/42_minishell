/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_struct_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:34:16 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/10 17:52:52 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quoted(char *token)
{
	int	i;

	i = 0;
	while ((token[i] != '\0') && (token[i] != '\n'))
	{
		if (((token[i] == '\'') || (token[i] == '\"'))
			&& is_paired(token[i], token, i + 1))
			return (token[i]);
		i++;
	}
	return (0);
}

int	set_redirections(t_data *data, char **token, int n, int qualif)
{
	char	*here_file;
	
	here_file = NULL;
	if (qualif == HERE_END)
	{
		here_file = get_here_file(data, token);
		add_tab(&(data->cmd[n].i), &(data->cmd[n].nr_in), here_file);
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

int	set_param(t_cmd *cmd, char **token)
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

int	classify_token(t_data *data, char **token, int n, int tok_nr)
{
	int	qualif;

	qualif = data->cmd[n].qualif[tok_nr];
	if ((qualif == CMD) || (qualif == PARAM))
		set_param(&(data->cmd[n]), token);
	else if ((qualif != OPERATOR) && (qualif != EMPTY))
		set_redirections(data, token, n, qualif);
	return (1);
}
