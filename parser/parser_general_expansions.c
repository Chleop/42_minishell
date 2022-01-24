/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_general_expansions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 13:16:12 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/24 15:59:11 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_one_command(char **envp, t_cmd *cmd)
{
	int		i;
	char	*temp;

	i = 0;
	while (i < (*cmd).nr_tok)
	{
		if ((*cmd).qualif[i] == CMD)
		{
			identify_remove_quotes((*cmd).tok[i]);
			tidy_token(data, (*token)[i]);
		}
		i++;
	}
	return (1);
}

int	expand_and_classify_others(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nr_cmds)
	{
		if (!expand_one_command(data->envp, &(data->cmd[i])))
			return (0);
		i++;
	}
	return (1);
}
