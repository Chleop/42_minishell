/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_struct_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:34:16 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/07 19:19:00 by cproesch         ###   ########.fr       */
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

int	set_redirections(t_data *data, char **token, int n, int qualif)
{
	if (qualif == RED_IN)
		add_tab(&(data->cmd[n].i), &(data->cmd[n].nr_in), *token);
	else if (qualif == HERE_END)
	{
		ft_free_parser(data, &token);
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

int	set_param(t_data *data, int n, char **token)
{
	static int	iterate;
	int			j;
	char		*par;

	j = 0;
	par = NULL;
	printf("before set param, token = %s\n", *token);
	while (1)
	{
		iterate = increment_quoted_part(iterate, token);
		if ((((*token)[iterate] == ' ') || (*token)[iterate] == '\0')
			|| ((*token)[iterate] == '\n'))
		{
			par = ft_substr(*token, j, iterate - j);
			if (!par)
				return (0);
			if (!add_tab(&(data->cmd[n].param), &(data->cmd[n].nr_param), par))
				return (0);
			free (par);
			if ((*token)[iterate] == '\0')
				return (1);
			j = iterate + 1;
		}
		iterate++;
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
		set_param(data, n, token);
	else if ((qualif != OPERATOR) && (qualif != EMPTY))
		set_redirections(data, token, n, qualif);
	return (1);
}
