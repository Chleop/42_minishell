/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_set_structure.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:54:01 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/26 17:58:22 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int expand_and_classify(t_data *data, char **token, int cmd_nr, int tok_nr)
{
	int	firstq_i;
	int	secondq_i;
	int	quote;

	quote = is_quoted(*token);
	if (quote)
	{
		firstq_i = ft_strchr(*token, quote) - *token;
		secondq_i = ft_strchr(*token + firstq_i + 1, quote) - *token;
		if (!remove_quotes(token, firstq_i, secondq_i))
			return (0);
	}
	if ((ft_strchr(data->cmd[cmd_nr].tok[tok_nr], '$')) && (quote != '\''))
		manage_expansions(data, token);
	if (!tidy_token(data, token, cmd_nr, tok_nr))
		return (0);
	return (1);
}

void    expand_cmd_path(t_data *data)
{
    int     i;
    char    *temp;

	i = 0;
	while (i < data->nr_cmds)
	{
        temp = data->cmd[i].param[0];
        data->cmd[i].param[0] = find_path(data->envp, data->cmd[i].param[0]);
		free (temp);
		i++;
	}
}

int	set_into_structure(t_data *data)
{
	int i;
	int	j;

	i = 0;
	while (i < data->nr_cmds)
	{
		j = 0;
		while (j < data->cmd[i].nr_tok)
		{
			if (!expand_and_classify(data, &(data->cmd[i].tok[j]), i, j))
				return (0);
			j++;
		}
		i++;
	}
	expand_cmd_path(data);
	return (1);
}
