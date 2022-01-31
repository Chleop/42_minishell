/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_set_structure.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:54:01 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/31 16:27:45 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_and_classify(t_data *data, char **token, int cmd_nr, int tok_nr)
{
	char	*temp;

	if (ft_strchr(data->cmd[cmd_nr].tok[tok_nr], '$'))
	{
		temp = *token;
		*token = manage_expansions(data, temp);
		if (!(*token))
			return (0);
		free (temp);
	}
	else
		identify_remove_quotes(token);
	if (!classify_token(data, token, cmd_nr, tok_nr))
		return (0);
	return (1);
}

void	expand_cmd_path(t_data *data)
{
	int		i;
	char	*temp;

	i = 0;
	while (i < data->nr_cmds)
	{
		if (!data->cmd[i].param)
			return ;
		temp = data->cmd[i].param[0];
		data->cmd[i].param[0] = find_path(data->envp, data->cmd[i].param[0]);
		free (temp);
		i++;
	}
}

int	set_into_structure(t_data *data)
{
	int	i;
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
