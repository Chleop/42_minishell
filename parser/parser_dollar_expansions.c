/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar_expansions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:34:16 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/24 15:59:13 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_one_dollar(char **envp, char	**token)
{
	int	i;
	int	firstq_i;
	int	secondq_i;

	i = 0;
	while ((*token)[i])
	{
		if ((*token)[i] == '\'')
		{
			firstq_i = i;
			secondq_i = is_paired((*token)[i], *token, i + 1);
			if (secondq_i)
				remove_quotes(token, firstq_i, secondq_i, &i);
			tidy_token(data, (*token)[i]);
		}
		else if ((*token)[i] == '\"')
		{
			firstq_i = i;
			secondq_i = is_paired((*token)[i], *token, i + 1);
			if (secondq_i)
				remove_quotes(token, firstq_i, secondq_i, &i);
			expand_variable((*token)[i]);
			tidy_token(data, (*token)[i]);
		}
		else
		{
			expand_variable((*token)[i]);
			tidy_token(data, (*token)[i]);
		}
		i++;
	}
	return (1);
}

int	expand_and_classify_dollars(t_data *data)
{
	int i;
	int	j;

	i = 0;
	while (i < data->nr_cmds)
	{
		j = 0;
		while (j < data->cmd[i].nr_tok)
		{
			if (ft_strchr(data->cmd[i].tok[i], '$'))
				expand_one_dollar(data->envp, &(data->cmd[i].tok[j]));
			j++;
		}
		i++;
	}
	return (1);
}
